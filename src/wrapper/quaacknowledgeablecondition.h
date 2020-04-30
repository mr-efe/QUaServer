#ifndef QUAACKNOWLEDGEABLECONDITION_H
#define QUAACKNOWLEDGEABLECONDITION_H

#include <QUaCondition>

#ifdef UA_ENABLE_SUBSCRIPTIONS_ALARMS_CONDITIONS

class QUaAcknowledgeableCondition : public QUaCondition
{
    Q_OBJECT

	Q_PROPERTY(bool confirmRequired READ confirmRequired WRITE setConfirmRequired)

friend class QUaServer;

public:
	Q_INVOKABLE explicit QUaAcknowledgeableCondition(
		QUaServer *server
	);

	// children

	QUaLocalizedText ackedStateCurrentStateName() const;
	void             setAckedStateCurrentStateName(const QUaLocalizedText& ackedState);
	bool             ackedStateId() const;
	void             setAckedStateId(const bool& ackedStateId);
	QDateTime        ackedStateTransitionTime() const;
	void             setAckedStateTransitionTime(const QDateTime& transitionTime);
	QUaLocalizedText ackedStateTrueState() const;
	void             setAckedStateTrueState(const QUaLocalizedText& trueState);
	QUaLocalizedText ackedStateFalseState() const;
	void             setAckedStateFalseState(const QUaLocalizedText& falseState);
	// helper sets setAckedStateId, setAckedStateCurrentStateName, setAckedStateTransitionTime 
	// and triggers event according to specification
	// NOTE : change of the Acked state must be normally make by the client through
	//        the use of the Acknowledge() and QUaAlarmCondition::Reset() methods
	bool acknowledged() const;
	void setAcknowledged(const bool& acknowledged);

	// NOTE: optional, only work if confirmRequired == true 
	QUaLocalizedText confirmedStateCurrentStateName() const;
	void             setConfirmedStateCurrentStateName(const QUaLocalizedText& confirmedState);
	bool             confirmedStateId() const;
	void             setConfirmedStateId(const bool& confirmedStateId);
	QDateTime        confirmedStateTransitionTime() const;
	void             setConfirmedStateTransitionTime(const QDateTime& transitionTime);
	QUaLocalizedText confirmedStateTrueState() const;
	void             setConfirmedStateTrueState(const QUaLocalizedText& trueState);
	QUaLocalizedText confirmedStateFalseState() const;
	void             setConfirmedStateFalseState(const QUaLocalizedText& falseState);
	// helper sets setConfirmedStateId, setConfirmedStateCurrentStateName, setConfirmedStateTransitionTime 
	// and triggers event according to specification
	// NOTE : change of the Confirmed state must be normally make by the client through
	//        the use of the Confirm() and QUaAlarmCondition::Reset() methods
	bool      confirmed() const;
	void      setConfirmed(const bool& confirmed);

	// methods

	Q_INVOKABLE void Acknowledge(QByteArray EventId, QUaLocalizedText Comment);

	Q_INVOKABLE void Confirm(QByteArray EventId, QUaLocalizedText Comment);

	// helpers

	bool confirmRequired() const;
	void setConfirmRequired(const bool & confirmRequired);

signals:
	void conditionAcknowledged();

	void conditionConfirmed();

protected:
	bool m_confirmRequired;
	// LocalizedText
	QUaTwoStateVariable* getAckedState();
	// LocalizedText
	QUaTwoStateVariable* getConfirmedState();

	// helpers

	// reimplement
	virtual bool requiresAttention() const override;
	// reimplement
	virtual void resetInternals() override;

};

class QUaAcknowledgeableConditionBranch : public QUaConditionBranch
{
public:
	QUaAcknowledgeableConditionBranch(
		QUaCondition* parent,
		const QUaNodeId& branchId = QUaNodeId()
	);

	bool acknowledged() const;
	void setAcknowledged(
		const bool& acknowledged, 
		const QUaLocalizedText& comment,
		const QString& currentUser = QString()
	);

	bool confirmed() const;
	void setConfirmed(
		const bool& confirmed, 
		const QUaLocalizedText& comment,
		const QString& currentUser = QString()
	);

protected:
	bool m_confirmRequired;

	// reimplement
	virtual bool requiresAttention() const override;

	// QUaAcknowledgeableCondition
	static QList<QUaQualifiedName> AckedState;
	static QList<QUaQualifiedName> AckedState_Id;
	static QList<QUaQualifiedName> AckedState_FalseState;
	static QList<QUaQualifiedName> AckedState_TrueState;
	static QList<QUaQualifiedName> AckedState_TransitionTime;
	static QList<QUaQualifiedName> ConfirmedState;
	static QList<QUaQualifiedName> ConfirmedState_Id;
	static QList<QUaQualifiedName> ConfirmedState_FalseState;
	static QList<QUaQualifiedName> ConfirmedState_TrueState;
	static QList<QUaQualifiedName> ConfirmedState_TransitionTime;

	friend QUaAcknowledgeableCondition;
};

#endif // UA_ENABLE_SUBSCRIPTIONS_ALARMS_CONDITIONS

#endif // QUAACKNOWLEDGEABLECONDITION_H