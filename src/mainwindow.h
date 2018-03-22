#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QDataWidgetMapper>
#include <QItemSelection>
#include <QMainWindow>
#include <QSettings>
#include <QTableView>

#include "contact.h"
#include "channel.h"
#include "contactsmodel.h"
#include "channelsmodel.h"
#include "database.h"
#include "intentsmodel.h"
#include "actionsmodel.h"
#include "logmodel.h"
#include "documentsmodel.h"
#include "documentproxymodel.h"
#include "contactproxymodel.h"
#include "intentproxymodel.h"
#include "actionproxymodel.h"
#include "logproxymodel.h"
#include "channelproxymodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum class AppMode {
        PANEL,
        CONTACTS
    };

    enum class PersonTab {
        PANEL,
        CONTACT,
        INTENTS,
        DOCUMENTS,
        LOG
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initialize();

signals:

private slots:
    void showMessage(const QString& label, const QString& text);

    void appModeSelectionChanged();
    void onContactFilterChanged(const QString& text);
    void onContactsListRowActivated(const QModelIndex &index);
    void onContactsListSelectionChanged(
            const QItemSelection &selected, const QItemSelection &deselected);
    void onContactsListCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void onContactsModelReset();
    void onSyncronizeContactsBindings();
    void onSyncronizePersonBindings();
    void onValidateContactActions();
    void onContactContextMenuRequested(const QPoint &pos);

    void onChannelContextMenuRequested(const QPoint &pos);
    void onChannelListRowActivated(const QModelIndex &index);
    void onChannelsModelReset();
    void onValidateChannelActions();

    void onPersonsContextMenuRequested(const QPoint &pos);
    void onPersonsListRowActivated(const QModelIndex &index);
    void onPersonsModelReset();
    void onPersonsClicked(const QModelIndex &index);
    void onValidatePersonsActions();

    void onIntentsContextMenuRequested(const QPoint &pos);
    void onIntentsRowActivated(const QModelIndex &index);
    void onIntentsModelReset();
    void onValidateIntentActions();

    void onActionsContextMenuRequested(const QPoint &pos);
    void onActionsRowActivated(const QModelIndex &index);
    void onActionsDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &);
    void onActionsModelReset();
    void onValidateActionActions();

    void onDocumentsContextMenuRequested(const QPoint &pos);
    void onDocumentsRowActivated(const QModelIndex &index);
    void onDocumentsDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &);
    void onDocumentsModelReset();
    void onValidateDocumentActions();

    void onContactTabChanged(int ix);

    void on_action_Quit_triggered();
    void on_actionAdd_Contact_triggered();

    void on_actionDelete_Contact_triggered();

    void on_actionAdd_Channel_triggered();

    void on_actionDelete_Channel_triggered();

    void on_actionEdit_Channel_triggered();

    void on_actionVerify_Channel_triggered();

    void on_actionCopy_Channel_to_Clipboard_triggered();

    void on_actionOpen_Channel_triggered();

    void on_actionAdd_Person_triggered();

    void on_actionAdd_Company_triggered();

    void on_actionEdit_Person_triggered();

    void on_actionDelete_Person_triggered();

    void on_actionAdd_Intent_triggered();

    void on_actionEdit_Intent_triggered();

    void on_actionDelete_Intent_triggered();

    void on_actionAdd_Action_triggered();

    void on_actionEdit_Action_triggered();

    void on_actionDelete_Action_triggered();

    void on_actionAction_Done_triggered();

    void on_actionExecute_Action_triggered();

    void on_actionMove_Action_Up_triggered();

    void on_actionMove_Action_Down_triggered();

    void on_actionAdd_Document_triggered();

    void on_actionEdit_Document_triggered();

    void on_actionDelete_Document_triggered();

    void on_actionOpen_Document_triggered();

    void on_actionSettings_triggered();

private:
    QString getChannelValue() const;
    ChannelType getChannelType() const;
    void createContact(ContactType type);
    void openChannel(const ChannelType type, const QString& value);
    bool confirmDelete(const QString& what);

    // Get the current person (either a company/contact - upper list) or a
    // person in a company (lower list), depending on the current context.

    // Return true if the current person is part of the selected company (lower list)
    bool isCurrentPersonInCompany() const;
    // Return the view for the current person
    QTableView *getCurrentPersonView() const;
    // Return the current selection index for the current person
    QModelIndex getCurrentPersonIndex() const;
    // return the model for the current person
    ContactsModel *getCurrentPersonModel() const;
    // returns 0 if no person is current and selected;
    int getCurrentPersonId() const;

    Ui::MainWindow *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
    AppMode app_mode_ = AppMode::PANEL;
    QSettings settings_;
    std::unique_ptr<Database> db_ = {};
    LogModel *log_model_ = {};
    LogProxyModel *log_px_model_ = {};
    ContactsModel *contacts_model_ = {};
    ContactsModel *persons_model_ = {}; // contact (persons) at a contact (company)
    ChannelsModel *channels_model_ = {};
    ChannelProxyModel *channels_px_model_ = {};
    IntentsModel *intents_model_ = {};
    IntentProxyModel *intents_px_model_ = {};
    ActionsModel *actions_model_ = {};
    ActionProxyModel *actions_px_model_ = {};
    DocumentsModel *documents_model_ = {};
    DocumentProxyModel *documents_px_model_ = {};
    ContactProxyModel *contact_px_model = {};
    ContactProxyModel * person_px_model = {};
    std::unique_ptr<QDataWidgetMapper> contacts_mapper_;
    std::unique_ptr<QDataWidgetMapper> persons_mapper_;
    int last_person_clicked {-1};
};

#endif // MAINWINDOW_H
