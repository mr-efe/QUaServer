#ifndef QUACONDITIONVARIABLE_H
#define QUACONDITIONVARIABLE_H

#include <QUaBaseDataVariable>

class QUaProperty;

// Part 9 - 5.3 : ConditionVariableType
/*
Various information elements of a Condition are not considered to be states. However, a change
in their value is considered important and supposed to trigger an Event Notification. These
information elements are called ConditionVariable.

*/

class QUaConditionVariable : public QUaBaseDataVariable
{
    Q_OBJECT

protected:
	// list for known children (standard instance declarations)
	static const QStringList mandatoryChildrenBrowseNames();

public:
	Q_INVOKABLE explicit QUaConditionVariable(
		QUaServer* server,
		const MC& mandatoryChildren = &QUaConditionVariable::mandatoryChildrenBrowseNames
	);

	// The time of the last change of the Value of this ConditionVariable
	// It shall be the same time that would be returned from the Read Service inside the DataValue
	// structure for the ConditionVariable Value Attribute.
	QDateTime sourceTimestamp() const;
	void setSourceTimestamp(const QDateTime& dateTime);

private:
	// UtcTime : 
	QUaProperty* getSourceTimestamp();

};

#endif // QUACONDITIONVARIABLE_H
