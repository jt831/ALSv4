#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RlsVector.generated.h"

UCLASS(Meta = (BlueprintThreadSafe))
class ALS_REFACTOR_REMAKE_API URlsVector : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "RLS|Vector Utility", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector ClampMagnitude01(const FVector& Vector);

	UFUNCTION(BlueprintPure, Category = "RLS|Vector Utility", DisplayName = "Clamp Magnitude 01 2D",
		Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector2D ClampMagnitude012D(const FVector2D& Vector);

	UFUNCTION(BlueprintPure, Category = "RLS|Vector Utility", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector AngleToDirectionXY(const float Angle);

	UFUNCTION(BlueprintPure, Category = "RLS|Vector Utility", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector RadiusToDirectionXY(const float Radius);
	
	UFUNCTION(BlueprintPure, Category = "RLS|Vector Utility", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector PerpendicularClockwiseXY(const FVector& Vector);
	
	UFUNCTION(BlueprintPure, Category = "RLS|Vector Utility", Meta = (AutoCreateRefTerm = "Vector", ReturnDisplayName = "Vector"))
	static FVector PerpendicularCounterClockwiseXY(const FVector& Vector);
};

inline FVector URlsVector::ClampMagnitude01(const FVector& Vector)
{
	// 将向量的长度映射到0到1区间
	// 通常用于保持运动权重的一致性
	const double MagnitudeSquared = Vector.SizeSquared();
	if (MagnitudeSquared <= 1.0f)
	{
		return Vector;
	}
	const double Scale = FMath::InvSqrt(MagnitudeSquared);

	return {Vector.X * Scale, Vector.Y * Scale, Vector.Z * Scale};
}

inline FVector2d URlsVector::ClampMagnitude012D(const FVector2D& Vector)
{
	const double MagnitudeSquared = Vector.SizeSquared();
	if (MagnitudeSquared <= 1.0f)
	{
		return Vector;
	}
	const double Scale = FMath::InvSqrt(MagnitudeSquared);
	
	return {Vector.X * Scale, Vector.Y * Scale};
}

inline FVector URlsVector::PerpendicularClockwiseXY(const FVector& Vector)
{
	return FVector(Vector.Y, Vector.X, 0.0f);
}

inline FVector URlsVector::PerpendicularCounterClockwiseXY(const FVector& Vector)
{
	return FVector(-Vector.Y, Vector.X, 0.0f);
}

inline FVector URlsVector::RadiusToDirectionXY(const float Radius)
{
	float sin, cos;
	FMath::SinCos(&sin, &cos, Radius);
	
	return FVector(cos, sin, 0.0f);
}

inline FVector URlsVector::AngleToDirectionXY(const float Angle)
{
	return RadiusToDirectionXY(FMath::DegreesToRadians(Angle));
}