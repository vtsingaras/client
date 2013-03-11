/*
 * Copyright (C) by Klaas Freitag <freitag@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef OWNCLOUDSETUPWIZARD_H
#define OWNCLOUDSETUPWIZARD_H

#include <QObject>
#include <QWidget>
#include <QNetworkReply>
#include <QPointer>

#include "mirall/owncloudwizard.h"
#include "mirall/connectionvalidator.h"
#include "mirall/theme.h"

namespace Mirall {

class SiteCopyFolder;
class SyncResult;
class ownCloudInfo;
class FolderScheduler;

class OwncloudSetupWizard : public QObject
{
    Q_OBJECT
public:
    explicit OwncloudSetupWizard( FolderScheduler *folderScheduler = 0, Theme *theme = 0, QObject *parent = 0 );

    ~OwncloudSetupWizard();

    /**
     * @intro wether or not to show the intro wizard page
     */
    void startWizard();

    void installServer();

    void writeOwncloudConfig();

    /**
   * returns the configured owncloud url if its already configured, otherwise an empty
   * string.
   */

    void    setupSyncFolder();

    OwncloudWizard *wizard();

signals:
    // issued if the oC Setup process (owncloud-admin) is finished.
    void    ownCloudSetupFinished( bool );
    // overall dialog close signal.
    void    ownCloudWizardDone( int );

public slots:

protected slots:
    // wizard dialog signals
    void slotConnectToOCUrl( const QString& );

   // void slotCreateRemoteFolder(bool);

private slots:
    void slotAssistantFinished( int );
    void slotClearPendingRequests();

    void slotConnectionResult( ConnectionValidator::Status );
    void showMsg(const QString&, const QString&);
private:
    //    bool createRemoteFolder( const QString& );
    void finalizeSetup( bool );

    /* Start a request to the newly installed ownCloud to check the connection */
    void testOwnCloudConnect();

    OwncloudWizard *_ocWizard;
    QPointer<QNetworkReply>  _mkdirRequestReply;
    QPointer<QNetworkReply>  _checkInstallationRequest;
    FolderScheduler      *_folderScheduler;
    ConnectionValidator *_conValidator;
    QString         _configHandle;
    QString         _localFolder;
    QString         _remoteFolder;
};

}

#endif // OWNCLOUDSETUPWIZARD_H
