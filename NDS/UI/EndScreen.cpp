#include "../UI/EndScreen.h"

void UEndScreen::NativeConstruct()
{
    Super::NativeConstruct();

    if (EndButton) {
        EndButton->OnClicked.AddDynamic(this, &UEndScreen::OnEndButtonClicked);
    }
}

void UEndScreen::OnEndButtonClicked()
{

}
