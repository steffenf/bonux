;8042 AT Keyboard controller driver

;0x60	Read	Read Input Buffer 8 bit
;0x60	Write	Write Output Buffer 8 bit
;0x64	Read	Read Status Register 8 bit
;0x64	Write	Send Command

;Status Register
;	b0	Output Buffer Full (OBF) 	Do not write output buffer when set to 1
;	b1	Input Buffer Full (IBF)		Something to read from input buffer when set to 1
;	b2	System Flag (SYS)		Read by POST. 1 if system is initialized, 0 if in
;						power on reset
;	b3	Address Line A2 (A2)		If 0, 0x60 last written to. If 1, 0x64 last written to
;	b4	Inhibit Flag (INH)		0: Keyboard is inhibited, 1: not inhibited
;	b5	Transmit Timeout (TxTO)		0: Keyboard accepted last byte written, 1: keyboard unp
;	b6	Receive TImeout (RxTO)		0: KEyboard processed last byte, 1: keyboard dead
;	b7	Parity Error (PARR)		0: Odd parity received ok, 1: Even parity or 0xFE as
;						command response

;Commands (all input gets to 0x60 read and all outputs (parameters) reads from 0x60 write

;0x20 (Read Command Byte) - Returns command byte.  (See "Write Command Byte" below).
;0x60 (Write Command Byte) - Stores parameter as command byte.  Command byte defined as follows:
;?0x90-0x9F (Write to output port) - Writes command's lower nibble to lower nibble of output port (see Output Port definition.)
;?0xA1 (Get version number) - Returns firmware version number.
;?0xA4 (Get password) - Returns 0xFA if password exists; otherwise, 0xF1.
;?0xA5 (Set password) - Set the new password by sending a null-terminated string of scan codes as this command's parameter.
;?0xA6 (Check password) - Compares keyboard input with current password.
;0xA7 (Disable mouse interface) - PS/2 mode only.  Similar to "Disable keyboard interface" (0xAD) command.
;0xA8 (Enable mouse interface) - PS/2 mode only.  Similar to "Enable keyboard interface" (0xAE) command.
;0xA9 (Mouse interface test) - Returns 0x00 if okay, 0x01 if Clock line stuck low, 0x02 if clock line stuck high, 0x03 if data line stuck low, and 0x04 if data line stuck high.
;0xAA (Controller self-test) - Returns 0x55 if okay.
;0xAB (Keyboard interface test) - Returns 0x00 if okay, 0x01 if Clock line stuck low, 0x02 if clock line stuck high, 0x03 if data line stuck low, and 0x04 if data line stuck high.
;0xAD (Disable keyboard interface) - Sets bit 4 of command byte and disables all communication with keyboard.
;0xAE (Enable keyboard interface) - Clears bit 4 of command byte and re-enables communication with keyboard.
;0xAF (Get version)
;0xC0 (Read input port) - Returns values on input port (see Input Port definition.)
;0xC1 (Copy input port LSn) - PS/2 mode only. Copy input port's low nibble to Status register (see Input Port definition)
;0xC2 (Copy input port MSn) - PS/2 mode only. Copy input port's high nibble to Status register (see Input Port definition.)
;0xD0 (Read output port) - Returns values on output port (see Output Port definition.) 
;0xD1 (Write output port) - Write parameter to output port (see Output Port definition.)
;0xD2 (Write keyboard buffer) - Parameter written to input buffer as if received from keyboard.
;0xD3 (Write mouse buffer) - Parameter written to input buffer as if received from mouse.
;0xD4 (Write mouse Device) - Sends parameter to the auxillary PS/2 device.
;0xE0 (Read test port) - Returns values on test port (see Test Port definition.)
;0xF0-0xFF (Pulse output port) - Pulses command's lower nibble onto lower nibble of output port (see Output Port definition.)
 


 
