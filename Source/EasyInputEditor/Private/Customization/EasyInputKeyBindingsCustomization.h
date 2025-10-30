// Copyright (C) Dreamer's Tail

#pragma once
#include "EasyInputBindings.h"
#include "IDetailCustomization.h"

enum class EEasyInputBindingType : uint8;
class UEasyInputBindings;


class FEasyInputActionKeyCustomization: public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	virtual void CustomizeHeader(
		TSharedRef<IPropertyHandle> StructPropertyHandle,
		class FDetailWidgetRow& HeaderRow,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

	virtual void CustomizeChildren(
		TSharedRef<IPropertyHandle> StructPropertyHandle,
		class IDetailChildrenBuilder& StructBuilder,
		IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

private:
	UEasyInputBindings* InputBindings = nullptr;

	static SHorizontalBox::FSlot::FSlotArguments PropertySlot(
		const TSharedPtr<IPropertyHandle>& PropertyHandle)
	{
		return MoveTemp(
		SHorizontalBox::Slot()
		.AutoWidth()
		[
			PropertyHandle->CreatePropertyValueWidget()
		]);
	}

	static SHorizontalBox::FSlot::FSlotArguments LabelSlot(
		const FString& Label)
	{
		return MoveTemp(
		SHorizontalBox::Slot()
		.Padding(4, 0)
		.AutoWidth()
		[
			SNew(SBox)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.WidthOverride(32)
			[
				SNew(STextBlock)
				.Text(FText::FromString(Label))
			]
		]);
	}
};


class SEasyInputActionKeyRow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEasyInputActionKeyRow) {}
		SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle)
		SLATE_ARGUMENT(FString, Label)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	void Draw();

	TSharedPtr<IPropertyHandle> PropertyHandle;
	FString Label;

	FReply OnButtonClicked();
};


class FEasyInputBindingsCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

private:
	virtual void CustomizeDetails(
		IDetailLayoutBuilder& DetailBuilder) override;

	void CustomizeBindings(
		IDetailLayoutBuilder& DetailBuilder,
		const FName& CategoryName,
		const EEasyInputBindingType Type) const;

	UEasyInputBindings* InputBindings = nullptr;
};


class SEasyInputRow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEasyInputRow)
		: _IconName(FName()) {}
		SLATE_ARGUMENT(FName, IconName)
		SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PropertyHandle)
		SLATE_ARGUMENT(FName, PropertyName)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};


class SEasyInputFunctions : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEasyInputFunctions) {}
		SLATE_ARGUMENT(UEasyInputBindings*, InputBindings)
		SLATE_ARGUMENT(EEasyInputBindingType, BindingType)
		SLATE_ARGUMENT(int32, BindingKey)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	UEasyInputBindings* InputBindings = nullptr;
	EEasyInputBindingType BindingType = EEasyInputBindingType::Action;
	int32 BindingKey = -1;

	TArray<TSharedPtr<FString>> Functions;

	TSharedRef<SWidget> OnGenerateWidget(
		TSharedPtr<FString> String);
	void OnSelectionChanged(
		TSharedPtr<FString> String,
		ESelectInfo::Type SelectInfo);
	bool IsComboEnabled() const;
};
