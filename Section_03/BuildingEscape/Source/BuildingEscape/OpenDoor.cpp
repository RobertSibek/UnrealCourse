// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"


bool bIsDoorOpen = false;

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	auto doorRotation = Owner->GetActorRotation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Door rotation is %s"), *doorRotation);

	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsDoorOpen) {
		UE_LOG(LogTemp, Warning, TEXT("I'm rotating"));		
		GetOwner()->SetActorRotation(FRotator(0.0f, -60.0f, 0.0f), ETeleportType::TeleportPhysics);
		bIsDoorOpen = true;
	}

	// ...
}

