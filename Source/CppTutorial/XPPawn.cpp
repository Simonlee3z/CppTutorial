// Fill out your copyright notice in the Description page of Project Settings.


#include "XPPawn.h"
#include "MoveComponent.h"

// Sets default values
AXPPawn::AXPPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup component hierarchy
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	RootComponent = PlayerMesh;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(PlayerMesh);

	MovementComponent->MaxSpeed = 600.f;  // 最大速度
	MovementComponent->Acceleration = 2048.f;  // 加速度
	MovementComponent->Deceleration = 2048.f;  // 减速度
}

// Called when the game starts or when spawned
void AXPPawn::BeginPlay()
{
	Super::BeginPlay();
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	
}

// Called every frame
void AXPPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXPPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXPPawn::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AXPPawn::Look);
		Input->BindAction(MoveudAction, ETriggerEvent::Triggered, this, &AXPPawn::UpAndDown);
	}


}

void AXPPawn::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Get forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

void AXPPawn::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AXPPawn::UpAndDown(const FInputActionValue& InputValue)
{
	float Value = InputValue.Get<float>();

	if (IsValid(Controller))
	{
		// 直接使用FVector::UpVector来表示向上的方向
		AddMovementInput(FVector::UpVector, Value);
		//添加日志输出调试确保值被正确处理
		//UE_LOG(LogTemp, Warning, TEXT("Up/Down Input Value: %f"), Value);
	}
}







