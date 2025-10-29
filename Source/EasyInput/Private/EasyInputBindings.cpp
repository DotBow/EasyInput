// Copyright (C) Dreamer's Tail

#include "EasyInputBindings.h"


UEasyInputBindings::UEasyInputBindings()
{
}

#if WITH_EDITOR
TArray<FString> UEasyInputBindings::GetSourceFunctions(
	const EEasyInputBindingType Type) const
{
	TArray<FString> FunctionNames;

	if (!FunctionsSource.IsNull())
	{
		UClass* LoadedClass = FunctionsSource.LoadSynchronous();
		const UStruct* Struct = Cast<UStruct>(LoadedClass);

		for (TFieldIterator<UFunction> FuncIt(Struct);
			FuncIt; ++FuncIt)
		{
			if (const UFunction* Function = *FuncIt; Function &&
				Function->HasAnyFunctionFlags(FUNC_BlueprintEvent) &&
				Function->HasMetaData("EasyInputFunction"))
			{
				if ((Type == EEasyInputBindingType::Action && Function->NumParms == 0) ||
					(Type == EEasyInputBindingType::Axis && Function->NumParms > 0))
				{
					FString FunctionName = Function->GetName();
					FunctionNames.Add(FunctionName);
				}
			}
		}
	}

	return FunctionNames;
}
#endif
