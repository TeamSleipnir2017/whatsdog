/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include <stdio.h>

/** Reset counter 10 seconds */
#define RST_MS_COUNTER                    10000
/** Watchdog period 3000ms */
#define WDT_PERIOD                        3000
/** LED blink time 300ms */
#define BLINK_PERIOD                      300
/** Watchdog restart 2000ms */
#define WDT_RESTART_PERIOD                2000


/** System Tick event flag */
volatile bool g_b_systick_event = false;
/** System tick increased by 1 every millisecond */
volatile uint32_t g_ul_ms_ticks = 0;
/** Reset counter decreased by 1 every millisecond */
volatile uint32_t ul_rst_counter;

void WDT_Handler(void)
{
	//puts("Enter watchdog interrupt.\r");

	/* Clear status bit to acknowledge interrupt by dummy read. */
	wdt_get_status(WDT);
	/* Restart the WDT counter. */
	wdt_restart(WDT);
	//puts("The watchdog timer was restarted.\r");
}


int main (void)
{
	
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();


 	uint32_t wdt_mode, timeout_value;
 	
 	/* Initialize reset counter */
 	ul_rst_counter = RST_MS_COUNTER;
 
 	
 	/* Get timeout value. */
 	timeout_value = wdt_get_timeout_value(WDT_PERIOD * 1000,
 	BOARD_FREQ_SLCK_XTAL);
 	if (timeout_value == WDT_INVALID_ARGUMENT) {
 		while (1) {
 			/* Invalid timeout value, error. */
 		}
 	}
 	
 	/* Configure WDT to trigger an interrupt (or reset). */
 	wdt_mode = WDT_MR_WDFIEN |  /* Enable WDT fault interrupt. */
 			WDT_MR_WDRPROC   |  /* WDT fault resets processor only. */
 			WDT_MR_WDDBGHLT  |  /* WDT stops in debug state. */
 			WDT_MR_WDIDLEHLT;   /* WDT stops in idle state. */
 	/* Initialize WDT with the given parameters. */
 
 	wdt_init(WDT, wdt_mode, timeout_value, timeout_value);
 	(int)wdt_get_us_timeout_period(WDT, BOARD_FREQ_SLCK_XTAL);
 
 	/* Configure and enable WDT interrupt. */
 	NVIC_DisableIRQ(WDT_IRQn);
 	NVIC_ClearPendingIRQ(WDT_IRQn);
 	NVIC_SetPriority(WDT_IRQn, 0);
	NVIC_EnableIRQ(WDT_IRQn);

	while(true){
		
		for (int i = 0; i < 100000000; i++)
		{
			if(i == 99999991){
				PIOB->PIO_CODR = PIO_PB27;
			}
			
		}
		while(1)
		{
			//inf loop
		}	
	}
	

}
