// Fill out your copyright notice in the Description page of Project Settings.


#include "XPCharacter.h"

// Sets default values
AXPCharacter::AXPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup component hierarchy
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->SetupAttachment(GetCapsuleComponent());
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AXPCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Allow character control pitch
	bUseControllerRotationPitch = true;
}

// Called every frame
void AXPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AXPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AXPCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AXPCharacter::Look);
		Input->BindAction(MoveudAction, ETriggerEvent::Triggered, this, &AXPCharacter::UpAndDown);
		Input->BindAction(ReversalAction, ETriggerEvent::Started, this, &AXPCharacter::BeginReversal);
		Input->BindAction(ReversalAction, ETriggerEvent::Completed, this, &AXPCharacter::EndReversal);
	}
}

void AXPCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Get forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

void AXPCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AXPCharacter::UpAndDown(const FInputActionValue& InputValue)
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

void AXPCharacter::BeginReversal(const FInputActionValue& InputValue)
{
	ATimeManager* ATM = AXPCharacter::GetTimeManagerInstance();
	ATM->BeginTimeReverse();
}

void AXPCharacter::EndReversal(const FInputActionValue& InputValue)
{
	ATimeManager* ATM = AXPCharacter::GetTimeManagerInstance();
	ATM->EndTimeReverse();
}

ATimeManager* AXPCharacter::GetTimeManagerInstance()
{
	for (TActorIterator<ATimeManager> It(GetWorld()); It; ++It)
	{
		return *It;
	}
	return nullptr;
}

