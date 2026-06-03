#include "../include/HLITE//Core.hpp"

int main(void)
{
    HLITE::CORE::APP::Run(
        HLITEMain::Init, 
        HLITEMain::Update,
        HLITEMain::Render, 
        HLITEMain::Unload
    );
    return 0;
}