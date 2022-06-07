// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MurosMoviles.generated.h"

UCLASS()
class STARFIGHTER_API AMurosMoviles : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMurosMoviles();

	// propiedad para el mesh del muro
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshCapsula;
	UPROPERTY()
		float AnchoM;
	UPROPERTY()
		float AltoM;

	UFUNCTION()
		void NotifyActorBeginOverlap(AActor* OtherActor)override;
	UPROPERTY()
		int IdentyM ;
	UFUNCTION()
		int GetIdentyM();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float MovementY; // movimiento en el eje y del muro
	float VelocidadMuro; // velocidad
	// variables para delimitar el campo del juego
	float AlturaCampo;
	float AnchoCampo;
	bool aux = true;
	FVector MoveDirection;
	FVector Movement;
	FRotator NewRotation;

	int Prueva;
	int MeshAleaotrio;
};
