// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// FOLLOWING LINE WILL CAUSE UE CRASH
	// FString ObjectName = GetOwner()->GetName();
	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	// HERE IT WORKS FINE
	FString ObjectName = GetOwner()->GetName();
	FString ObjectPosA = GetOwner()->GetActorLocation().ToString();
	FString ObjectPosO = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Position report for %s, actor location is %s, owner location is %s"), *ObjectName, *ObjectPosA, *ObjectPosO);

	// ...
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FVector ObjectPosition = GetOwner()->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Position report for %s = %d"), *ObjectName, ObjectPosition.X);

	// ...
}

