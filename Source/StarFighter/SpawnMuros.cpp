// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnMuros.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnMuros::ASpawnMuros()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
}

// Called when the game starts or when spawned
void ASpawnMuros::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnMuros::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (SpawnMuros.Num() <= 0)
    {
        return;
    }
    const int Index = FMath::RandRange(0, SpawnMuros.Num() - 1);

    SpawnCoolDown += DeltaTime;
    if (SpawnCoolDown >= NextSpawnCoolDown)
    {
        FVector Location = WhereToSpawn->GetComponentLocation();
        float Y = WhereToSpawn->GetScaledBoxExtent().Y;
        Location.Y = FMath::RandRange(Location.Y - Y, Location.Y + Y);
        UE_LOG(LogTemp, Warning, TEXT("Should Spawn at: %s"), *Location.ToString());
        SpawnCoolDown = 0.0f;
        FRotator Rotation = GetActorRotation();
        Rotation.Pitch = 0.0;
        GetWorld()->SpawnActor(SpawnMuros[Index], &Location, &Rotation);
    }
}

