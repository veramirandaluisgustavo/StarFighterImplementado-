// Fill out your copyright notice in the Description page of Project Settings.


#include "MurosMoviles.h"
#include "UObject/ConstructorHelpers.h"
#include "time.h"

// Sets default values
AMurosMoviles::AMurosMoviles()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsuleMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	MeshCapsula = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroMesh"));
	MeshCapsula->SetStaticMesh(CapsuleMesh.Object);

	AlturaCampo = 950.f;
	AnchoCampo = 850.f;
}

// Called when the game starts or when spawned
void AMurosMoviles::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMurosMoviles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	srand(time(NULL));
	MovementY = rand() % 14 - 5;
	VelocidadMuro = 40.f;

	// esta condicion hace que el muro rebote una ves que choque a los cantos
	if (aux) {
		if (this->GetActorLocation().Y < AnchoCampo) {
			MoveDirection = FVector(-1.0f, MovementY, 0.0f);
			Movement = MoveDirection * VelocidadMuro * DeltaTime;

			if (Movement.SizeSquared() > 0.0f) {
				NewRotation = FRotator(0.f, 0.f, 0.f);

				FHitResult Hit(1.0f);
				RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
			}
			if (this->GetActorLocation().Y > AnchoCampo) { aux = false; }
		}
	}
	else {
		if (this->GetActorLocation().Y > -AnchoCampo) {
			MoveDirection = FVector(-1.0f, -MovementY, 0.0f);
			Movement = MoveDirection * VelocidadMuro * DeltaTime;

			if (Movement.SizeSquared() > 0.0f) {
				NewRotation = FRotator(0.f, 0.f, 0.f);

				FHitResult Hit(1.0f);
				RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
			}
			if (this->GetActorLocation().Y < -AnchoCampo) { aux = true; }
		}
	}

	// condicion para que el muro se destruya
	if (this->GetActorLocation().X < -AlturaCampo) {
		this->Destroy();
	}
}

// Called to bind functionality to input
void AMurosMoviles::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

