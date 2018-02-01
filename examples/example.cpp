// #include "tiva/tiva.hpp"
// #include "tiva/chip/tm4c123gh6pm.hpp"

// using namespace tiva::gpio;
// using namespace tiva::uart;

#include <tuple>
#include <type_traits>
#include <cstdint>
#include <cassert>

#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/uart.h"

using CharType = unsigned char;

union RxData
{
    constexpr RxData(std::uint32_t value)
        :   _value(value)
    {}

    struct {
        char data;
        bool framingError : 1;
        bool parityError : 1;
        bool breakError : 1;
        bool overrunError : 1;
    };

    bool isValid() const
    {
        return (_value & 0x00F);
    }

private:
    std::uint32_t _value;
};

enum class TxFIFOLevel
{
	_1_8 = UART_IFLS_TX1_8,
	_1_4 = UART_IFLS_TX1_4,
	_1_2 = UART_IFLS_TX1_2,
	_3_4 = UART_IFLS_TX3_4,
	_7_8 = UART_IFLS_TX7_8,
};

enum class RxFIFOLevel
{
	_1_8 = UART_IFLS_RX1_8,
	_1_4 = UART_IFLS_RX1_4,
	_1_2 = UART_IFLS_RX1_2,
	_3_4 = UART_IFLS_RX3_4,
	_7_8 = UART_IFLS_RX7_8,
};

class UART
{
public:
    UART(std::uint32_t base);

    void disable();
    void disableFIFOs();
    void disableLoopBack();
    void disableNow();
    void disableRx();
    void disableTx();
    void enable();
    void enableFIFOs();
    void enableLoopBack();
    void enableRx();
    void enableTx();
    void flushTxFIFO();
    RxData getRxData();
    RxData getRxDataNow();
    std::pair<RxFIFOLevel, TxFIFOLevel> getFIFOsLevels() const;
    RxFIFOLevel getRxFIFOLevel() const;
    TxFIFOLevel getTxFIFOLevel() const;
    bool isEnabled() const;
    bool isRxEmpty() const;
    bool isRxEnabled() const;
    bool isRxFull() const;
    bool isTxEmpty() const;
    bool isTxEnabled() const;
    bool isTxFull() const;
    bool isWriting() const;
    void putChar(CharType c);
    void putCharNow(CharType c);
    void setFIFOsLevels(RxFIFOLevel rxFIFOLevel, TxFIFOLevel txFIFOLevel);
    void setRxFIFOLevel(RxFIFOLevel rxFIFOLevel);
    void setTxFIFOLevel(TxFIFOLevel txFIFOLevel);
    bool tryGetRxData(RxData& c);
    bool tryPutChar(CharType c);

private:
    const std::uint32_t _base;
};

inline
UART::UART(std::uint32_t base)
    :   _base(base)
{}

inline void
UART::disable()
{
	while(isWriting());	// wait for end of transmission
	flushTxFIFO(); // ???
	disableNow();
}

inline void
UART::disableFIFOs()
{
	HWREG(_base + UART_O_LCRH) &= (~UART_LCRH_FEN);
}

inline void
UART::disableLoopBack()
{
	HWREG(_base + UART_O_CTL) &= (~UART_CTL_LBE);
}

inline void
UART::disableNow()
{
	HWREG(_base + UART_O_CTL) &= ~UART_CTL_UARTEN;
}

inline void
UART::disableRx()
{
	HWREG(_base + UART_O_CTL) &= ~UART_CTL_RXE;
}

inline void
UART::disableTx()
{
	HWREG(_base + UART_O_CTL) &= ~UART_CTL_TXE;
}

inline void
UART::enable()
{
	HWREG(_base + UART_O_CTL) |= UART_CTL_UARTEN;
}

inline void
UART::enableFIFOs()
{
	HWREG(_base + UART_O_LCRH) |= UART_LCRH_FEN;
}

inline void
UART::enableLoopBack()
{
	HWREG(_base + UART_O_CTL) |= UART_CTL_LBE;
}

inline void
UART::enableRx()
{
	HWREG(_base + UART_O_CTL) |= UART_CTL_RXE;
}

inline void
UART::enableTx()
{
	HWREG(_base + UART_O_CTL) |= UART_CTL_TXE;
}

inline void
UART::flushTxFIFO()
{
	disableTxFIFO();
}

inline std::pair<RxFIFOLevel, TxFIFOLevel>
UART::getFIFOsLevels() const
{
	const auto value = (HWREG(_base + UART_O_IFLS));
	const rxFIFOLevel = static_cast<RxFIFOLevel>(maskedValue & UART_IFLS_RX_M);
	const txFIFOLevel = static_cast<TxFIFOLevel>(maskedValue & UART_IFLS_TX_M);

	assert(isRxFIFOLevelValid(rxFIFOLevel));
	assert(isTxFIFOLevelValid(txFIFOLevel));

	return std::make_pair(rxFIFOLevel, txFIFOLevel);
}

inline UART::RxData
UART::getRxData()
{
	assert(isRxEnabled());

	while(isRxEmpty()); // wait until a char is available.

	return getRxDataNow();
}

inline UART::RxData
UART::getRxDataNow()
{
	assert(isRxEnabled());

    return(RxData(HWREG(_base + UART_O_DR)));
}

inline RxFIFOLevel
UART::getRxFIFOLevel() const
{
	const auto maskedValue = (HWREG(_base + UART_O_IFLS) & UART_IFLS_RX_M);
	const rxFIFOLevel = static_cast<RxFIFOLevel>(maskedValue);

	assert(isRxFIFOLevelValid(rxFIFOLevel));

	return rxFIFOLevel;
}

inline TxFIFOLevel
UART::getTxFIFOLevel() const
{
	const auto maskedValue = (HWREG(_base + UART_O_IFLS) & UART_IFLS_TX_M);
	const txFIFOLevel = static_cast<TxFIFOLevel>(maskedValue);

	assert(isTxFIFOLevelValid(txFIFOLevel));

	return txFIFOLevel;
}

inline bool
UART::isEnabled() const
{
	return (HWREG(_base + UART_O_CTL) & UART_CTL_UARTEN);
}

inline bool
UART::isRxEmpty() const
{
	return (HWREG(_base + UART_O_FR) & UART_FR_RXFE);
}

inline bool
UART::isRxEnabled() const
{
    return (HWREG(_base + UART_O_CTL) & UART_CTL_RXE);
}

inline bool
UART::isRxFull() const
{
	return (HWREG(_base + UART_O_FR) & UART_FR_RXFF);
}

inline bool
UART::isTxEmpty() const
{
	return (HWREG(_base + UART_O_FR) & UART_FR_TXFE);
}

inline bool
UART::isTxEnabled() const
{
    return (HWREG(_base + UART_O_CTL) & UART_CTL_RXE);
}

inline bool
UART::isTxFull() const
{
	return (HWREG(_base + UART_O_FR) & UART_FR_TXFF);
}

inline bool
UART::isWriting() const
{
	return (HWREG(_base + UART_O_FR) & UART_FR_BUSY);
}

inline void
UART::putChar(CharType c)
{
	assert(isTxEnabled());

	while(isTxFull());
	putCharNow(c);
}

inline void
UART::putCharNow(CharType c)
{
	assert(isTxEnabled());

	HWREG(_base + UART_O_DR) = c;
}

inline void
UART::setFIFOsLevels(RxFIFOLevel rxFIFOLevel, TxFIFOLevel txFIFOLevel)
{
	HWREG(_base + UART_O_IFLS) = static_cast<std::uint32_t>(rxFIFOLevel)
		| static_cast<std::uint32_t>(txFIFOLevel);
}

inline void
UART::setRxFIFOLevel(RxFIFOLevel rxFIFOLevel)
{
	const auto currentValue = HWREG(_base + UART_O_IFLS);
	const auto clearedValue = (currentValue & (~UART_IFLS_RX_M));
	HWREG(_base + UART_O_IFLS) =
		(clearedValue | static_cast<decltype(clearedValue)>(rxFIFOLevel));
}

inline void
UART::setTxFIFOLevel(TxFIFOLevel txFIFOLevel)
{
	const auto currentValue = HWREG(_base + UART_O_IFLS);
	const auto clearedValue = (currentValue & (~UART_IFLS_TX_M));
	HWREG(_base + UART_O_IFLS) =
		(clearedValue | static_cast<decltype(clearedValue)>(txFIFOLevel));
}

inline bool
UART::tryGetRxData(RxData& rxData)
{
	assert(isRxEnabled());

	if(isRxEmpty())
	{
		return false;
	}

	getRxDataNow(rxData);
}

inline bool
UART::tryPutChar(CharType c)
{
	assert(isTxEnabled());

	if(isTxFull())
	{
		return false;
	}

	putCharNow(c);
}


int main()
{
	while(1);
}
