#pragma once

#include "SoundEngine/music.h"
#include "SoundEngine/sound.h"
#include "imagesource.h"
#include "ifont.h"

class QString;
struct WOGBall;
struct AnimationData;
class WOGEffect;
struct WOGMaterial;

namespace og
{
struct IResourceManager
{
    virtual ~IResourceManager()
    {
    }

    virtual bool ParseResourceFile(const QString& a_filename) = 0;

    virtual bool ParseTextFile(const QString& a_filename, const QString& a_language) = 0;

    virtual bool ParseFxFile(const QString& a_filename) = 0;

    virtual bool ParseMaterialsFile(const QString& a_filename) = 0;

    virtual const WOGBall* GetBallByType(const QString& a_type) = 0;

    virtual ImageSourceSPtr GetImageSourceById(const QString& a_id) = 0;

    virtual og::audio::Music* GetMusic(const QString& a_id) = 0;

    virtual SoundSPtr GetSound(const QString& a_id) = 0;

    virtual const audio::SoundSource* GetSoundSource(const QString& a_id) = 0;

    virtual void ClearAllSoundSources() = 0;

    virtual const IFont* GetFont(const QString& aId) = 0;

    virtual QString GetText(const QString& aId) = 0;

    virtual AnimationData* GetAnimation(const QString& aId) = 0;

    virtual const WOGEffect* GetEffect(const QString& aId) = 0;

    virtual const WOGMaterial* GetMaterial(const QString& aId) = 0;
};
}
