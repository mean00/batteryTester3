

class UserSettings
{
public:
    int     resistor1000; // 1000x the wiring resistor
    int     initialDischargeMa;
    int     minimumVoltage;  
    
    void    loadSettings();
    void    saveSettings();
};