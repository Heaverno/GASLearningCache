// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyGameWorldWidget.h"
#include <Kismet/GameplayStatics.h>
#include <UMG/Public/Blueprint/WidgetLayoutLibrary.h>
#include <UMG/Public/Components/SizeBox.h>

void UMyGameWorldWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();
		UE_LOG(LogTemp, Warning, TEXT("Attached actor no longer valid, removing Health Widget."));
		return;
	}

	FVector2D ScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
