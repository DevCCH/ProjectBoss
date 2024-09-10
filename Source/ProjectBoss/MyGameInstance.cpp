// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Person.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

void UMyGameInstance::Init()
{
	Super::Init();

	CourseInfo = NewObject<UCourseInfo>(this);

	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("최창휘"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("김성은"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("최김창은"));

	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::OnCourseInfoChanged);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::OnCourseInfoChanged);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::OnCourseInfoChanged);

	CourseInfo->ChangeCourseInfo(TEXT("학교"), TEXT("프로그래밍"));
}

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교");
}
