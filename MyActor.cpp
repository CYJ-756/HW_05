// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	start = FVector2D::ZeroVector;
	totDist = 0.0f;
	evCnt = 0;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("Start"));
	move();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMyActor::distance(const FVector2D first, FVector2D second) {
	float dx = second.X - first.X;
	float dy = second.Y - first.Y;
	return FMath::Sqrt(dx * dx + dy * dy);
}


int32 AMyActor::step() {
	return FMath::RandRange(0, 1);
}


int32 AMyActor::createEvent()
{
	int32 isEvent = FMath::RandRange(0, 1);
	if (isEvent) {
		evCnt++;
	}
	return isEvent;
}

int32 AMyActor::eventType()
{
	int32 isEvent = FMath::RandRange(0, 2);
	return isEvent;
}

void AMyActor::move() {
	FVector2D prev = start;
	UE_LOG(LogTemp, Log, TEXT("Step 0: (%.0f, %.0f)"), start.X, start.Y);
	
	for (int32 i = 1; i <= 10; ++i)
	{
		prev = start;
		int32 dx = step();
		int32 dy = step();
		start.X += dx;
		start.Y += dy;

		float dist = distance(prev, start);
		totDist += dist;

		int32 eventHappened = createEvent();
		
		if (eventHappened == 0) {
			UE_LOG(LogTemp, Log, TEXT("Step %d: (%.0f, %.0f )| length: %.2f | event: NO"),
				i, start.X, start.Y, dist);
		}
		else {
			FString eventName;
			switch (eventType()) {
				case 0: eventName = TEXT("Item"); break;
				case 1: eventName = TEXT("Gold"); break;
				case 2: eventName = TEXT("Monster"); break;
				default: eventName = TEXT("error"); break;
			}
			UE_LOG(LogTemp, Log, TEXT("Step %d: (%.0f, %.0f )| length: %.2f | event: %s"),
				i, start.X, start.Y, dist, *eventName);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("total length: %.2f"), totDist);
	UE_LOG(LogTemp, Warning, TEXT("total event: %d"), evCnt);
}
