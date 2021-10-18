#include "GJLampType.generated.h"

UENUM()
enum EGJLampType
{
	Constant UMETA(DisplayName = "Constant"),
	OnOff UMETA(DisplayName = "OnOff"),
	Connected UMETA(DisplayName = "Connected"),
};