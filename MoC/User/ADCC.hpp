#ifndef ADCC_HPP_
#define ADCC_HPP_

#include "stm32g4xx.h"
#include "adc.h"

class ADCC{
public:
	static ADCC &getInstance(){
		static ADCC _adcc_instance;
		return _adcc_instance;
	}

    void init();

private:
	ADCC(){}
	ADCC(const ADCC &other);
	ADCC &operator=(const ADCC &other);

    uint16_t adc1_data=0;
    uint16_t adc2_data=0;

};


#endif