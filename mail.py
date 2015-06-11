#!/usr/bin/python

import smtplib

sender = 'email@email.com'
receivers = ['receivers@email.com']

message = """From: Raspberry pi <raspberry001@email.com>
To: IT Support
Subject: Temperature alert!!

The server is very hot !!!!!!!
"""


#try:
smtpObj = smtplib.SMTP('smtp.email.com',25)
smtpObj.sendmail(sender, receivers, message)         
#   print "Successfully sent email"
#except SMTPException:
#   print "Error: unable to send email"
