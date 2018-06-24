#pragma once

#include "particlepool.h"

#include <list>
#include <array>

class QPainter;

class WOGEffect;

namespace og
{
class ParticleSystem;
class ParticleEmiter;

typedef std::shared_ptr<ParticleEmiter> ParticleEmiterSPtr;

struct ParticleDefination
{
    struct AxialSinOffset
    {
        std::array<int, 2> amp;
        std::array<float, 2> freq;
        std::array<float, 2> phaseshift;

        void SetAmplitude(const QPoint& aAmp)
        {
            AssignValueToArray(amp, aAmp);
        }

        void SetFrequency(const QPointF& aFreq)
        {
            AssignValueToArray(freq, aFreq);
        }

        void SetPhaseshift(const QPointF& aPhaseshift)
        {
            AssignValueToArray(phaseshift, aPhaseshift);
        }
    };

    int direction;
    int dirvar;
    std::vector<ImageSourceSPtr> imageSources;
    std::array<float, 2> speed;
    std::array<float, 2> scale;
    std::pair<bool, float> finalScale;
    std::pair<bool, QPointF> lifespan;
    std::pair<bool, QPointF> rotationSpeed;
    std::pair<bool, float> dampening;
    std::pair<bool, AxialSinOffset> xAxialSinOffset;
    std::pair<bool, AxialSinOffset> yAxialSinOffset;
    bool shouldFade;
    bool isDirected;
    bool isAdditive;
    QPoint rotation;
    QPointF acceleration;

    ParticleDefination()
        : direction(0)
        , dirvar(0)
        , shouldFade(false)
        , isDirected(false)
        , isAdditive(false)
    {
        SetSpeed(QPointF(0, 0));
        SetScale(QPointF(1.0f, 1.0f));
        finalScale.first = false;
        lifespan.first = false;
        dampening.first = false;
        xAxialSinOffset.first = false;
        yAxialSinOffset.first = false;
    }

    void AddImageSource(ImageSourceSPtr& aSource)
    {
        imageSources.push_back(aSource);
    }

    void SetSpeed(const QPointF& aSpeed)
    {
        AssignValueToArray(speed, aSpeed);
    }

    void SetScale(const QPointF& aScale)
    {
        AssignValueToArray(scale, aScale);
    }

private:
    template<typename TArray, typename TValue>
    static void AssignValueToArray(TArray& aArray, const TValue& aVal)
    {
        assert(aArray.size() == 2);

        aArray[0] = aVal.x();
        aArray[1] = aVal.y();
    }
};

struct ParticleEmiterDefination;

class ParticleEmiter
{
public:
    enum Type
    {
        e_unknown,
        e_point,
        e_ambient,
        e_user
    };

    friend class ParticleSystem;

public:
    ParticleEmiter(int aMaxParticles, ParticleSystem* aSystem)
        : mParticlePool(aMaxParticles)
        , mParticleSystem(aSystem)
    {
    }

    virtual ~ParticleEmiter()
    {
    }

    virtual void PreUpdate()
    {
    }

    void Update();

    virtual void PostUpdate()
    {
    }

    void Render(QPainter& aPainter)
    {
        foreach (auto particle, mUpdate)
        {
            particle->Render(aPainter);
        }
    }

    Particle* AddParticle(Particle* aParticle)
    {
        mUpdate.push_back(aParticle);
        return aParticle;
    }

    void AddParticleDefination(ParticleDefination& aDefination)
    {
        mParticleDefinations.push_back(aDefination);
    }

    ParticleSystem* GetParticleSystem() const
    {
        return mParticleSystem;
    }

    int GetMaxPirticles() const
    {
        return mParticlePool.GetMaxParticleCount();
    }

    int GetCountParticles() const
    {
        return mUpdate.size();
    }

    Particle* PopParticle()
    {
        if (mUpdate.empty())
        {
            return nullptr;
        }

        Particle* p = mUpdate.front();
        p->Init();
        mUpdate.pop_front();
        return p;
    }

    void Emit(const QPointF& aPosition, const ParticleDefination aDef);

    void Emit(const QPointF& aPosition);

protected:
    ParticlePool mParticlePool;
    std::list<Particle*> mUpdate;
    std::list<ParticleEmiterSPtr>::iterator mIterator;
    ParticleSystem* mParticleSystem;
    std::vector<ParticleDefination> mParticleDefinations;
};

struct ParticleEmiterDefination
{
    ParticleEmiter::Type type;
    int maxparticles;
    int margin;
    int  timeoutInterval;
    float rate;
};
} // ns:og