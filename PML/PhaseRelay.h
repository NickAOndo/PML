/*******************************************************************
  ** Author: Nicholas Ondo
  ** License: MIT
  ** Description: PhaseRelay header file. 
*******************************************************************/

#ifndef PM_PHASERELAY_H
#define PM_PHASERELAY_H
namespace pm{

class PhaseRelay
{
    public:
        PhaseRelay();
        virtual ~PhaseRelay();
        PhaseRelay(const PhaseRelay& other);
        PhaseRelay& operator=(const PhaseRelay& other);

		bool gameStatus;
		unsigned int frames;
    protected:
    private:
};

}
#endif // PHASERELAY_H
