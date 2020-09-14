// Fill out your copyright notice in the Description page of Project Settings.


#include "PathManager.h"


#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"

std::string UPathManager::Path;

void UPathManager::OpenFileDialog(const FString& DialogTitle, const FString& DefaultPath, const FString& FileTypes,
                                  TArray<FString>& OutFileNames)
{
    if (GEngine)
    {
        if (GEngine->GameViewport)
        {
            void* ParentWindowHandle = GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle();
            IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
            if (DesktopPlatform)
            {
                //Opening the file picker!
                uint32 SelectionFlag = 0;
                //A value of 0 represents single file selection while a value of 1 represents multiple file selection
                DesktopPlatform->OpenFileDialog(ParentWindowHandle, DialogTitle, DefaultPath, FString(""), FileTypes,
                                                SelectionFlag, OutFileNames);
            }
        }
    }
}

void UPathManager::PrintData(const FString& File)
{
    //Parse the data into a string array
    TArray<FString> LoadedText;
    FFileHelper::LoadFileToStringArray(LoadedText, *File);
    //Print the contents
    for (int32 i = 0; i < LoadedText.Num(); i++)
    {
        GLog->Log(LoadedText[i]);
    }
}

void UPathManager::SetPath(const FString& p)
{
    Path = std::string(TCHAR_TO_UTF8(*p));
}

std::string UPathManager::GetPath()
{
    return Path;
}
