#include <assert.h>
#include <iostream>
using namespace std;

#define MIN_TEMP_THRESHOLD			0
#define MAX_TEMP_THRESHOLD			45
#define MIN_STATE_OF_CHARGE			20
#define MAX_STATE_OF_CHARGE			80
#define CHARGE_RATE					0.8


class BatteryParams {
private:
	float temperature;
	float soc;
	float chargeRate;
	float dischargeRate;
	const float minSOC = MIN_STATE_OF_CHARGE;
	const float maxSOC = MAX_STATE_OF_CHARGE;
	const float minTemp = MIN_TEMP_THRESHOLD;
	const float maxTemp = MAX_TEMP_THRESHOLD;
	const float maxChargeRate = CHARGE_RATE;
public:
	BatteryParams(float temperature, float soc, float chargeRate);
	void UpdateParams(float temperature, float soc, float chargeRate);
	bool ValidateTemperature();
	bool ValidateStateOfCharge();
	bool ValidateChargeRate();
};

BatteryParams::BatteryParams(float inputTemp, float inputsoc, float inputchargeRate) {
	temperature = inputTemp;
	soc = inputsoc;
	chargeRate = inputchargeRate;
}

void BatteryParams::UpdateParams(float inputTemp, float inputsoc, float inputchargeRate) {
	temperature = inputTemp;
	soc = inputsoc;
	chargeRate = inputchargeRate;
}

bool BatteryParams::ValidateTemperature() {
	if (temperature < minTemp || temperature > maxTemp) {
		cout << "Temperature out of range!\n";
		return false;
	}
	else {
		return true;
	}
}
bool BatteryParams::ValidateStateOfCharge() {

	if (soc < minSOC || soc > maxSOC) {
		cout << "State of Charge out of range!\n";
		return false;
	}else {
		return true;
	}
}

bool BatteryParams::ValidateChargeRate() {

	if (chargeRate > maxChargeRate) {
		cout << "Charge Rate out of range!\n";
		return false;
	}
	else {
		return true;
	}
}

bool ValidateBattery(BatteryParams * batterystatus) {
	bool rc = false;
	rc = (batterystatus->ValidateTemperature() && batterystatus->ValidateChargeRate() && batterystatus->ValidateStateOfCharge());
	return rc;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
	class BatteryParams* batterystats  = new BatteryParams(temperature, soc, chargeRate);
	bool results=false;
	results = ValidateBattery(batterystats);
	delete batterystats;
	retrun results;
}


int main() {
	assert(batteryIsOk(25, 70, 0.7) == true);
	assert(batteryIsOk(50, 85, 0) == false);
	assert(batteryIsOk(25, 70, 0.9) == false);
	assert(batteryIsOk(0, 90, 0.9) == false);
}
