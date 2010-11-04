
/*
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * ``The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is SimpleAmqpClient for RabbitMQ.
 *
 * The Initial Developer of the Original Code is Alan Antonuk.
 * Original code is Copyright (C) Alan Antonuk.
 *
 * All Rights Reserved.
 *
 * Contributor(s): ______________________________________.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU General Public License Version 2 or later (the "GPL"), in
 * which case the provisions of the GPL are applicable instead of those
 * above. If you wish to allow use of your version of this file only
 * under the terms of the GPL, and not to allow others to use your
 * version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the
 * notice and other provisions required by the GPL. If you do not
 * delete the provisions above, a recipient may use your version of
 * this file under the terms of any one of the MPL or the GPL.
 *
 * ***** END LICENSE BLOCK *****
 */

#include "Connection.h"
#include "Channel.h"
#include "BasicMessage.h"

#include <iostream>

using namespace AmqpClient;
int main()
{
	Connection::ptr_t conn = Connection::Create("127.0.0.1", 5672);
	Channel::ptr_t channel = conn->CreateChannel();

	channel->DeclareQueue("alanqueue");
	channel->BindQueue("alanqueue", "amq.direct", "alankey");

	BasicMessage::ptr_t msg_in = BasicMessage::Create();

	msg_in->Body("This is a small message.");

	channel->BasicPublish("amq.direct", "alankey", msg_in);

	channel->BasicConsume("alanqueue", "consumertag");

	BasicMessage::ptr_t msg_out = channel->BasicConsumeMessage();

	std::cout << "Message text: " << msg_out->Body() << std::endl;

}

