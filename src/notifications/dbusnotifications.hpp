#pragma once

#ifdef USE_DBUS

#include "lib/log.hpp"

#include <QList>
#include <QTextDocument>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusInterface>
#include <QCoreApplication>

/**
 * Notifications using d-bus through the
 * org.freedesktop.Notifications interface
 */
class DbusNotifications
{
public:
	DbusNotifications();

	auto getCapabilities() -> QList<QString>;

	void notify(const QString &title, const QString &message,
		const QString &imagePath, int timeout);

private:
	QDBusConnection dbus;
	unsigned int notificationId = 0;

	auto isConnected() -> bool;
};

#endif