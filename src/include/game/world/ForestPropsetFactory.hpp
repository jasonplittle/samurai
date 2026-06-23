#pragma once

#include "Props.hpp"


class ForestPropsetFactory
{
public:
    static std::unique_ptr<PropSet> CreatePropset()
    {
        std::unique_ptr<PropSet> propSet = std::make_unique<PropSet>();

        glm::vec2 frameSize;
        
        frameSize = glm::vec2(120, 160);
        propSet->Set[PropId::Tree1] = 
        {
            .Size = frameSize,
            .AnimationClip
            {
                .IsStill = true,
                .FrameSize = frameSize,
                .Sprite = std::make_unique<Sprite>("resources/props/Tree1.png", frameSize)
            },
        };

        frameSize = glm::vec2(120, 160);
        propSet->Set[PropId::Tree2] = 
        {
            .Size = frameSize,
            .AnimationClip
            {
                .IsStill = true,
                .FrameSize = frameSize,
                .Sprite = std::make_unique<Sprite>("resources/props/Tree2.png", frameSize)
            },
        };

        frameSize = glm::vec2(120, 160);
        propSet->Set[PropId::Tree3] = 
        {
            .Size = frameSize,
            .AnimationClip
            {
                .IsStill = true,
                .FrameSize = frameSize,
                .Sprite = std::make_unique<Sprite>("resources/props/Tree3.png", frameSize)
            },
        };

        // propSet.Set[PropId::Bush1] = 
        // {
        //     .Size = glm::vec2(60, 32),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Bush1.png", glm::vec2(60, 32))
        // };

        // propSet.Set[PropId::Bush2] = 
        // {
        //     .Size = glm::vec2(14, 32),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Bush2.png", glm::vec2(14, 32))
        // };

        // frameSize = glm::vec2(14, 32);
        // propSet.Set[PropId::Bush3] = 
        // {
        //     .AnimationClip
        //     {
        //         .IsStill = true,
        //         .FrameSize = frameSize,
        //         .Sprite = std::make_unique<Sprite>("resources/props/Bush3.png", frameSize)
        //     },
        // };

        // propSet.Set[PropId::Bush4] = 
        // {
        //     .Size = glm::vec2(40, 32),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Bush4.png", glm::vec2(40, 32))
        // };

        // propSet.Set[PropId::Bush5] = 
        // {
        //     .Size = glm::vec2(40, 32),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Bush5.png", glm::vec2(40, 32))
        // };

        // propSet.Set[PropId::Bush6] = 
        // {
        //     .Size = glm::vec2(24, 32),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Bush6.png", glm::vec2(24, 32))
        // };

        // propSet.Set[PropId::Bush7] = 
        // {
        //     .Size = glm::vec2(20, 32),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Bush7.png", glm::vec2(20, 32))
        // };

        // propSet.Set[PropId::Lamp] = 
        // {
        //     .Size = glm::vec2(32, 96),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Lamp.png", glm::vec2(32, 96))
        // };

        // propSet.Set[PropId::Torii] = 
        // {
        //     .Size = glm::vec2(98, 96),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Torii.png", glm::vec2(98, 96))
        // };

        // propSet.Set[PropId::Well] = 
        // {
        //     .Size = glm::vec2(78, 96),
        //     .Sprite = std::make_unique<Sprite>("resources/props/Well.png", glm::vec2(78, 96))
        // };


        frameSize = glm::vec2(29, 64);
        propSet->Set[PropId::Flag] = 
        {
            .Size = frameSize,
            .AnimationClip
            {
                .StartFrame = 0,
                .FrameCount = 6,
                .FrameDuration = 0.1,
                .Loop = true,
                .FrameSize = frameSize,
                .Sprite = std::make_unique<Sprite>("resources/props/Flag.png", frameSize)
            },
        };

        return propSet;
    }
};