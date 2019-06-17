/**
 *  @file   include/MCParticle.cc
 *
 *  @brief  Header file for the MCParticle class.
 *
 *  $Log: $
 */

#ifndef MCPARTICLE_H
#define MCPARTICLE_H 1

#include <TLorentzVector.h>

typedef std::vector<int> IntVector;
typedef std::vector<float> FloatVector;
typedef std::pair<TLorentzVector, TLorentzVector> TrajectoryPoint;
typedef std::vector<TrajectoryPoint> TrajectoryPointVector;
typedef std::vector<int, std::string> TrajectoryProcessVector;

/**
 *  @brief MCParticle class
 */
class MCParticle
{
public:
    /**
     *  Default constructor
     */
    MCParticle();

    /**
     *  Constructor
     */
    MCParticle(const int trackId, const int pdg, const int parent, const double mass, const int status);

    /**
     *  Destructor
     */
    ~MCParticle();

    /**
     *  @brief Trajectory class
     */
    class Trajectory
    {
    public:
        /**
         *  Default constructor
         */
        Trajectory();

        /**
         *  Constructor
         */
        Trajectory(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV);

        const TLorentzVector &GetPosition(const int i) const;
        const TLorentzVector &GetMomentum(const int i) const;
        double GetPositionX(const int i) const;
        double GetPositionY(const int i) const;
        double GetPositionZ(const int i) const;
        double GetMomentumX(const int i) const;
        double GetMomentumY(const int i) const;
        double GetMomentumZ(const int i) const;
        double GetEnergy(const int i) const;
        int GetNumberOfTrajectoryPoints() const;

        void AddTrajectoryPoint(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV);

    private:
        TrajectoryPointVector m_trajectoryPointVector;
    };

    int GetStatus() const;
    int GetTrackId() const;
    int GetPDGCode() const;
    int GetParent() const;
    double GetMass() const;

    void AddDaughter(const int trackId);
    int GetDaughter(const int trackId) const;
    int GetNumberOfDaughters() const;

    int GetNumberOfTrajectoryPoints() const;

    const TLorentzVector &GetPosition(const int i = 0) const;
    double GetPositionX(const int i = 0) const;
    double GetPositionY(const int i = 0) const;
    double GetPositionZ(const int i = 0) const;
    double GetTime(const int i = 0) const;

    const TLorentzVector &GetEndPosition() const;
    double GetEndPositionX() const;
    double GetEndPositionY() const;
    double GetEndPositionZ() const;
    double GetEndTime() const;

    const TLorentzVector &GetMomentum(const int i = 0) const;
    double GetMomentumX(const int i = 0) const;
    double GetMomentumY(const int i = 0) const;
    double GetMomentumZ(const int i = 0) const;
    double GetEnergy(const int i = 0) const;
    double GetStepMomentum(const int i = 0) const;

    const TLorentzVector &GetEndMomentum() const;
    double GetEndMomentumX() const;
    double GetEndMomentumY() const;
    double GetEndMomentumZ() const;
    double GetEndEnergy() const;

    void AddTrajectoryPoint(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV);

private:
    int         m_status;
    int         m_trackId;
    int         m_pdgCode;
    int         m_parent;
    std::string m_process;
    std::string m_endProcess;
    Trajectory  m_trajectory;
    float       m_mass;
    IntVector   m_daughters;
};

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetStatus() const
{
    return m_status;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetTrackId() const
{
    return m_trackId;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetPDGCode() const
{
    return m_pdgCode;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetParent() const
{
    return m_parent;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMass() const
{
    return m_mass;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void MCParticle::AddDaughter(const int trackId)
{
    m_daughters.push_back(trackId);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetDaughter(const int trackId) const
{
    if (std::abs(trackId) < m_daughters.size())
        m_daughters.at(trackId);

    return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetNumberOfDaughters() const
{
    return m_daughters.size();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::GetNumberOfTrajectoryPoints() const
{
    return m_trajectory.GetNumberOfTrajectoryPoints();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetPosition(const int i) const
{
    return m_trajectory.GetPosition(i);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetPositionX(const int i) const
{
    return m_trajectory.GetPosition(i).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetPositionY(const int i) const
{
    return m_trajectory.GetPosition(i).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetPositionZ(const int i) const
{
    return m_trajectory.GetPosition(i).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetTime(const int i) const
{
    return m_trajectory.GetPosition(i).T();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetEndPosition() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndPositionX() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndPositionY() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndPositionZ() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndTime() const
{
    return m_trajectory.GetPosition(m_trajectory.GetNumberOfTrajectoryPoints() - 1).T();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetMomentum(const int i) const
{
    return m_trajectory.GetMomentum(i);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMomentumX(const int i) const
{
    return m_trajectory.GetMomentum(i).Px();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMomentumY(const int i) const
{
    return m_trajectory.GetMomentum(i).Py();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetMomentumZ(const int i) const
{
    return m_trajectory.GetMomentum(i).Pz();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEnergy(const int i) const
{
    return m_trajectory.GetMomentum(i).E();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetStepMomentum(const int i) const
{
    return std::sqrt(std::pow(m_trajectory.GetMomentum(i).E(), 2) - std::pow(m_mass, 2));
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline const TLorentzVector &MCParticle::GetEndMomentum() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1);
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndMomentumX() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Px();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndMomentumY() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Py();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndMomentumZ() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).Pz();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::GetEndEnergy() const
{
    return m_trajectory.GetMomentum(m_trajectory.GetNumberOfTrajectoryPoints() - 1).E();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline void MCParticle::AddTrajectoryPoint(const TLorentzVector &vtxTLV, const TLorentzVector &momentumTLV)
{
    m_trajectory.AddTrajectoryPoint(vtxTLV, momentumTLV);
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetPositionX(const int i) const
{
    return this->GetPosition(i).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetPositionY(const int i) const
{
    return this->GetPosition(i).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetPositionZ(const int i) const
{
    return this->GetPosition(i).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetMomentumX(const int i) const
{
    return this->GetMomentum(i).X();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetMomentumY(const int i) const
{
    return this->GetMomentum(i).Y();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetMomentumZ(const int i) const
{
    return this->GetMomentum(i).Z();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline double MCParticle::Trajectory::GetEnergy(const int i) const
{
    return this->GetMomentum(i).E();
}

//------------------------------------------------------------------------------------------------------------------------------------------ 

inline int MCParticle::Trajectory::GetNumberOfTrajectoryPoints() const
{
    return m_trajectoryPointVector.size();
}

#endif // #ifndef MCPARTICLE_H
