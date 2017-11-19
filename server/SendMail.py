import smtplib
import time
import User


def sendRegisterEmail(purpose,username,email):
#Purpose - register || inactive

    gmail_mail = 'teampoker8@gmail.com'
    gmail_password = 'StraightFlush'

    sent_from = gmail_mail
    to = email
    subject = "Welcome to Poker"
    if(purpose == "register"):
        body = 'Hello '+ username+'\n\n Welcome to Poker. Thank you for register ,have a nice day and come steal some chips.\n Best regards: \n\n Your Poker Team'
    elif(purpose == "inactive"):
        body = 'Hello ' + username + '\n\n You have been inactive for quite a while. Come and play..\n Best regards: \n\n Your Poker Team'

    message = """From: %s\nTo: %s\nSubject: %s\n%s
        """ % (sent_from, "".join(to), subject, body)
    try:
        server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
        server.ehlo()
        server.login(gmail_mail, gmail_password)
        server.sendmail(sent_from, to, message)
        server.close()

        print('Email sent!')
        return 1
    except:
        print('Something went wrong...')
        return 0



def notifyInactivePlayer():
    users = User.getAllInactiveUsers();
    for user in users:
            sendRegisterEmail("inactive",user[1],user[2])
    time.sleep(1814400000)

while True:
    notifyInactivePlayer()