/* 
 * File  :  crystal_display.h
 * Author:  João Cruz       - 76517
 *          Henrique Martins- 76674    
 */
#ifndef CRYSTAL_DISPLAY_H
#define        CRYSTAL_DISPLAY_H
#ifdef        __cplusplus
extern "C" {
#endif
#if 1
// Helper Macros for common commands
#define mLCDClear() SendCommandToLCD(0x01)            // Clears screen and cursor
#define mLCDScrollRight() SendCommandToLCD(0x1E)      // Scroll display one character right
#define mLCDScrollLeft() SendCommandToLCD(0x18)       // Scroll display one character left
#define mLCDCursorHome() SendCommandToLCD(0x02)       // Cursor moves to top left
#define mLCDCursorRight() SendCommandToLCD(0x14)      // Move cursor right one
#define mLCDCursorLeft() SendCommandToLCD(0x10)       // Move cursor left one
#define mLCDUnderlineCursor() SendCommandToLCD(0x0E)  // Visible underline cursor
#define mLCDBlinkingCursor() SendCommandToLCD(0x0F)   // Visible blinking cursor
#define mLCDHideCursor() SendCommandToLCD(0x0C)       // Invisible cursor
#define mLCDHideDisplay() SendCommandToLCD(0x08)      // Blank display (without clearing)
#define mLCDRestoreDisplay() SendCommandToLCD(0x0C)   // Restore display (with cursor hidden)
// Set cursor to the specified row and column
#define mLCDSetCursor(row, column) SendCommandToLCD(0x80 | ((row << 6) + column))
#endif
void InitPorts(void);
void InitialiseDisplay(void);
void ResetDisplay(void);
void SendCommandToLCD(uint8_t uiCommand);
void LCDSendString(char * str);
void LCDSendChar(char character);
void delay(uint32_t period);
uint8_t DecToASCII(uint8_t number);
void UpdateL1(void);
void UpdateL2(uint8_t nr2);
void UpdateL3(void);
#ifdef        __cplusplus
}
#endif
#endif        /* CRYSTAL_DISPLAY_H */