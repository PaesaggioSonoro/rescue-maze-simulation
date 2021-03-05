#include "Driver.hpp"

#include "MainMaze/robot/data/Directions.hxx"
#include "MainMaze/robot/utils/Math.hxx"


#if _EXECUTION_ENVIRONMENT == 0

void Driver::Rotate(const bool right)
{
	Lasers* lasers = Lasers::Instance();
	Gyro* gyro = Gyro::Instance();
	const int direction_multiplier = right ? 1 : -1;
	float c = lasers->ReadF(), r = lasers->ReadFr(), l = lasers->ReadFl();

	if (Lasers::IsValidWall(l, c, r))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid wall, centralizing"));
		if (right)
		{
			GetBus()->SetSpeed(-20, 20);
			while (lasers->ComputeFrontDifference() > 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
			GetBus()->SetSpeed(50, -50);
			while (lasers->ComputeFrontDifference() < 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
		}
		else
		{
			GetBus()->SetSpeed(20, -20);
			while (lasers->ComputeFrontDifference() < 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
			GetBus()->SetSpeed(-50, 50);
			while (lasers->ComputeFrontDifference() > 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
		}
	}


	gyro->Calibrate();
	const float start = gyro->Yaw();
	float goal = math::ClampAngle(start + 85 * direction_multiplier);
	float current = start;


	while (right ? RightTurnCondition(start, current, goal) : LeftTurnCondition(start, current, goal))
	{
		FPlatformProcess::Sleep(0.1);
		current = gyro->Yaw();
		UE_LOG(LogTemp, Warning, TEXT("MAIN -> starting: %f, objective: %f, current: %f"), start, goal, current);
	}
	c = lasers->ReadF(), r = lasers->ReadFr(), l = lasers->ReadFl();
	GetBus()->SetSpeed(10 * direction_multiplier, -10 * direction_multiplier);
	float diff = lasers->ComputeFrontDifference();
	if (Lasers::IsValidWall(l, c, r))
	{
		while (right ? diff < 0 : diff > 0)
		{
			FPlatformProcess::Sleep(0.001);
			diff = lasers->ComputeFrontDifference();
			UE_LOG(LogTemp, Warning, TEXT("FINAL -> difference: %f"), diff);
		}
	}
	else
	{
		goal = math::ClampAngle(start + 90 * direction_multiplier);
		while (right ? RightTurnCondition(start, current, goal) : LeftTurnCondition(start, current, goal))
		{
			FPlatformProcess::Sleep(0.001);
			current = gyro->Yaw();
			UE_LOG(LogTemp, Warning, TEXT("FINAL -> starting: %f, objective: %f, current: %f"), start, goal, current);
		}
	}
	GetBus()->SetSpeed(0, 0);
}

void Driver::Go()
{
	Lasers* lasers = Lasers::Instance();
	Gyro* gyro = Gyro::Instance();
	gyro->Calibrate();

	const float front_distance = lasers->ReadF(), back_distance = lasers->ReadB();
	const float start_rotation = gyro->Yaw();
	const bool use_front = front_distance < back_distance;
	float current_distance = use_front ? front_distance : back_distance;
	const int cells = static_cast<int>(current_distance) / static_cast<int>(cell_dimensions::depth);
	const float objective = std::max(
		5.f, (cells + (use_front ? -1 : 1)) * cell_dimensions::depth + (cell_dimensions::depth -
			dimensions::depth) / 2);
	int speed;
	float delta_yaw = 0;
	bool compensating = false;
	while (use_front ? current_distance > objective : current_distance < objective)
	{
		const float c = lasers->ReadF(), r = lasers->ReadFr(), l = lasers->ReadFl();
		const float lateral = lasers->ComputeLateralDifference();
		const bool near = c < objective + 5;
		float distance_component = std::max(1.f, current_distance / cell_dimensions::depth);

		bool is_valid_wall = Lasers::IsValidWall(l, c, r);

		float current_angle = gyro->Yaw();
		float delta_angle = math::AngleDifference(current_angle, start_rotation);

		if (abs(delta_angle) > degree_override_threshold_)
		{
			speed = kSlow;
			compensating = true;
			delta_yaw = stuck_compensation_multiplier_ * (delta_angle > 0 ? 1 : -1);
		}
		else if (is_valid_wall)
		{
			compensating = false;
			delta_yaw = Lasers::FrontDifference(l, r) * frontal_compensation_multiplier_;
			speed = near ? kMedium : kFast;
			delta_yaw /= distance_component;
			if (lateral < lateral_compensation_threshold_ && lateral > -lateral_compensation_threshold_)
			{
				delta_yaw += math::Clamp(lateral * lateral_compensation_multiplier_, -max_lateral_compensation_speed_,
				                         max_lateral_compensation_speed_);
			}
		}
		else
		{
			speed = kMedium;
			if (!compensating)
			{
				compensating = true;
				delta_yaw = stuck_compensation_multiplier_ * (delta_yaw > 0 ? -1 : 1);
			}
		}


		UE_LOG(LogTemp, Warning,
		       TEXT(
			       "objective: %f, missingcells: %d, distance: %f, speed: %d, deltayaw: %f, dc: %f, laser: %hs, compensating: %d"
		       ),
		       objective, cells, current_distance, speed, delta_yaw, distance_component, use_front?"front":"back",
		       compensating);
		UE_LOG(LogTemp, Warning, TEXT("direction: %d, startangle: %f, currentangle: %f, anglediff: %f"), is_valid_wall,
		       start_rotation, current_angle, delta_angle);
		GetBus()->SetSpeed(speed - delta_yaw, speed + delta_yaw);
		FPlatformProcess::Sleep(near ? 0.01 : 0.2);
		if (is_valid_wall) current_distance = use_front ? lasers->ReadF() : lasers->ReadB();
	}
	GetBus()->SetSpeed(0, 0);
}

bool Driver::RightTurnCondition(const float start, const float current, const float goal)
{
	if (goal >= start)
	{
		return start <= current && current <= goal;
	}
	return start <= current && current <= 360 || 0 <= current && current <= goal;
}

bool Driver::LeftTurnCondition(const float start, const float current, const float goal)
{
	if (goal < start)
	{
		return goal <= current && current <= start;
	}
	return 0 <= current && current <= start || goal <= current && current <= 360;
}
#endif
