// Fill out your copyright notice in the Description page of Project Settings.


#include "PathContainer.h"

string UPathContainer::path;

void UPathContainer::setPath(const FString& p) {
	path = string(TCHAR_TO_UTF8(*p));
}

string UPathContainer::getPath() {
	if (path.length() > 0) {
		return path;
	}
	else {
		return "C:\\Users\\Winblu\\Downloads\\main.json";
	}
	
}
