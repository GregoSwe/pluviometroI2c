/*
 * @File: ActionSendInteger.h
 *
 * @Creation Date: 19/DIC/2014
 *
 * @Last Update: 23/GEN/2015
 *
 * @Version: 1.0
 *
 * @Author: Gregorini Marco
 *
 * @Email: gregorini.marco91@gmail.com
 *
 * @Licence: This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef ACTIONSENDINTEGER_h
#define ACTIONSENDINTEGER_h

#include"AbstractAction.h"
#include <Wire.h>
class ActionSendInteger : public AbstractAction
{
private:
   unsigned int intToSend;
public:
    ActionSendInteger(int _intToSend, AbstractAction *_otherAction);
    //ActionSendInteger(int _intToSend);
    virtual void execute();
    virtual ~ActionSendInteger(){}
};

#endif
