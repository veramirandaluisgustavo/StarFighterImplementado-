// Fill out your copyright notice in the Description page of Project Settings.


#include "MurosMoviles.h"
#include "UObject/ConstructorHelpers.h"
#include "time.h"

// Sets default values
AMurosMoviles::AMurosMoviles()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshAleaotrio = FMath::RandRange(1, 3);
	if (MeshAleaotrio == 1) {
		static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsuleMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		MeshCapsula = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroMesh"));
		MeshCapsula->SetStaticMesh(CapsuleMesh.Object);
		RootComponent = MeshCapsula;
	}
	if (MeshAleaotrio == 2) {

		static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsuleMesh(TEXT("StaticMesh'/Game/Meshes/MuroA.MuroA'"));
		MeshCapsula = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroMesh"));
		MeshCapsula->SetStaticMesh(CapsuleMesh.Object);
		RootComponent = MeshCapsula;
	}
	else {

		static ConstructorHelpers::FObjectFinder<UStaticMesh> CapsuleMesh(TEXT("StaticMesh'/Game/Meshes/MuroA1.MuroA1'"));
		MeshCapsula = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroMesh"));
		MeshCapsula->SetStaticMesh(CapsuleMesh.Object);
		RootComponent = MeshCapsula;
	}
	
	
	
	
	AlturaCampo = 950.f;
	AnchoCampo = 850.f;

	IdentyM = 8989;


	//AnchoM = FMath::RandRange(1, 2);
	//AltoM = FMath::RandRange(1, 1.5);
	//MeshCapsula->SetRelativeTransform(FTransform(FRotator(), FVector(), FVector(AnchoM, AltoM, 1)));
}

void AMurosMoviles::NotifyActorBeginOverlap(AActor* OtherActor)
{
	

		//this->Destroy();

	
	


}

int AMurosMoviles::GetIdentyM()
{

	return IdentyM;
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

