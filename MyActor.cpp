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
	move();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMyActor::distance(const FVector2D first, FVector2D second) {
	return FVector2D::Distance(first, second);
}

int32 AMyActor::step() {
	return FMath::RandRange(0, 1);
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

		UE_LOG(LogTemp, Log, TEXT("Step %d: (%.0f, %.0f )| length: %.2f | event: %s"), 
			i, start.X, start.Y ,dist, eventHappened ? TEXT("Yes") : TEXT("No"));
	}
	UE_LOG(LogTemp, Warning, TEXT("total length: %.2f"), totDist);
	UE_LOG(LogTemp, Warning, TEXT("total event: %d"), evCnt);
}

int32 AMyActor::createEvent()
{
	int32 isEvent = FMath::RandRange(0, 1);
	if (isEvent) evCnt++;
	return isEvent;
}