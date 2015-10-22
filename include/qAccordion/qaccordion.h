// This file is part of qAccordion. An Accordion widget for Qt
// Copyright © 2015 Christian Rapp <0x2a at posteo dot org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef QACCORDION_H
#define QACCORDION_H

#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QSpacerItem>
#include <QString>
#include <QPropertyAnimation>
#include <QDebug>

#include <vector>
#include <map>
#include <memory>
#include <algorithm>

#include "contentpane.h"

/**
 * @brief The QAccordion class
 *
 *
 *
 */
class QAccordion : public QWidget
{
    Q_OBJECT
public:
    explicit QAccordion(QWidget *parent = 0);

    /**
     * @brief Returns the number of content panes
     * @return int
     */
    int numberOfContentPanes();

    /**
     * @brief Add a new content Pane
     * @param header Header of the content pane
     * @return Content pane index
     *
     * @details
     * Use this method to add a new content pane with the Header header.
     * The method will return the index of the new content pane, or <b>-1</b> if
     * the pane was not added because \p header already exists.
     */
    int addContentPane(QString header);
    /**
     * @brief Add a new content Pane
     * @param header Header of the content pane
     * @param contentFrame The content of the pane
     * @return Content pane index
     *
     * @details
     * This is an overloaded method of addContentPane(QString), that
     * allows you to provide your own content frame.
     */
    int addContentPane(QString header, QFrame *contentFrame);
    /**
     * @brief Add content pane
     * @param cpane New content pane to add
     * @return Content pane index
     *
     * @details
     * This is an overloaded method of addContentPane(QString), that
     * allows you to provide your own content pane.
     */
    int addContentPane(ContentPane *cpane);
    /**
     * @brief Insert content pane
     * @param index Index of the content pane
     * @param header Header of the content pane
     * @return bool True if insert was successfull
     *
     * @details
     * You can use this method to insert a new content pane at given index with
     * \p header defining the Header. An empty content pane will be created that
     * you can get with getContentPane().
     *
     * Returns true if the insert was successfull.
     */
    bool insertContentPane(uint index, QString header);
    /**
     * @brief Insert content pane
     * @param index Index of the content pane
     * @param header Header of the content pane
     * @param contentFrame Content frame of the content pane
     * @return bool True if insert was successfull
     *
     * @details
     * This is an overloaded method of insertContentPane(uint, QString).
     * Use this method when you already created a content frame that you want to
     * insert.
     */
    bool insertContentPane(uint index, QString header, QFrame *contentFrame);
    /**
     * @brief Insert content pane
     * @param index Index of the content pane
     * @param cpane Content Pane to insert
     * @return bool True if insert was successfull
     *
     * @details
     * This is an overloaded method of insertContentPane(uint, QString).
     * Use this method when you already created a content pane that you want to
     * insert.
     */
    bool insertContentPane(uint index, ContentPane *cpane);

    /**
     * @brief Swap the content pane
     * @param index Index of the content pane to swap
     * @param newContentPane New content pane
     * @return bool True if swap was successfull
     *
     * @details
     * With this method you can replace an existing content pane at \p index with
     * a new one \p contentPane.
     *
     * Returns true if the swap was successfull.
     *
     * The old content pane will be __deleted__.
     */
    bool swapContentPane(uint index, ContentPane *cpane);

    /**
     * @brief Remove a content pane
     * @param index Index of the content pane
     * @return bool
     *
     * @details
     * Remove a content pane at \p index.
     *
     * Returns true if the pane was deleted and false otherwise.
     */
    bool removeContentPane(uint index);
    /**
     * @brief Remove a content pane
     * @param header Header of the content pane
     * @return bool
     *
     * @details
     * This is an overloaded method of removeContentPane(uint).
     */
    bool removeContentPane(QString header);
    /**
     * @brief Remove a content pane
     * @param contentframe Content frame of the content pane
     * @return bool
     *
     * @details
     * This is an overloaded method of removeContentPane(uint).
     */
    bool removeContentPane(QFrame *contentframe);
    /**
     * @brief Remove a content pane
     * @param contentPane The content pane to remove
     * @return bool
     *
     * @details
     * This is an overloaded method of removeContentPane(uint).
     */
    bool removeContentPane(ContentPane *contentPane);

    /**
     * @brief Move content pane
     * @param currentIndex The current index of the content pane.
     * @param newIndex The new index of the current pane
     * @return bool
     *
     * @details
     * Moves a content from \p currentIndex to \p newIndex. Returns true if the
     * content pane was moved, false otherwise.
     */
    bool moveContentPane(uint currentIndex, uint newIndex);

    /**
     * @brief Enable or disable content pane
     * @param index Index of the content pane
     * @param disable
     * @return bool
     *
     * @details
     * Enable or disable a content pane at \p index. The status can be set with
     * \p  disable. This disables the header as well and it can longer be clicked.
     *
     * Method returns true if the content pane was disabled (enabled), false
     * otherwise.
     *
     * To disable all content panes use [QAccordion::setDisabled(bool)](http://doc.qt.io/qt-5.5/qwidget.html#setDisabled).
     */
    bool setDisabledContentPane(uint index, bool disable);
    /**
     * @brief Enable or disable content pane
     * @param header Content pane header
     * @param disable
     * @return bool
     *
     * @details
     * This is an overloaded function of moveContentPane(uint, uint). Instead of
     * an index you can provide the Header.
     */
    bool setDisabledContentPane(QString header, bool disable);
    /**
     * @brief Enable or disable content pane
     * @param contentPane Content pane
     * @param disable
     * @return bool
     *
     * @details
     * This is an overloaded function of moveContentPane(uint, uint). Instead of
     * an index you can provide a content pane.
     */
    bool setDisabledContentPane(QFrame *contentPane, bool disable);

    /**
     * @brief Get content pane
     * @param index Index of the content pane
     * @return QFrame* or nullptr
     *
     * @details
     * Get a content pane (QFrame*) with \p index. This method will return a
     * __nullptr__ if the content pane does not exist.
     */
    ContentPane *getContentPane(uint index);
    /**
     * @brief Get the index of a content pane
     * @param contentPane ContentPane*
     * @return Index of the content pane
     *
     * @details
     * Get the index of a provided content pane (ContentPane*) this method will return
     * <b>-1</b> if the content pane does not exist.
     */
    int getContentPaneIndex(ContentPane *contentPane);
    /**
     * @brief Get the number of content panes
     * @return Number of content panes
     */
    int getNumberOfContentPanes();

    /**
     * @brief Get error string
     * @return Error string
     *
     * @details
     * Call this method after a function call returned false for a detailed error
     * description.
     */
    QString getError();

signals:
    /**
     * @brief Signals the new number of content panes
     * @param number Number of content panes
     *
     * @details
     * Signal will be emitted if the number of content panes changes
     */
    void numberOfContentPanesChanged(int number);


public slots:

    /**
     * @brief Open content pane
     * @param index Index of the content pane
     *
     * Open the content pane at index. If the content pane is already open
     * nothing will haben.
     */
    void openContentPane(uint index);
    /**
     * @brief Close content pane
     * @param index Index of the content pane
     *
     * Close the content pane at \p index. If the content pane is already closed
     * nothing will haben.
     */
    void closeContentPane(uint index);

private:

    std::vector<ContentPane *> contentPanes;

    QSpacerItem *spacer;

    QString errorString;

    int internalAddContentPane(QString header, QFrame *cframe = nullptr,
                               ContentPane *cpane = nullptr);
    bool internalInsertContentPane(uint index, QString header,
                                   QFrame *contentFrame = nullptr,
                                   ContentPane *cpane = nullptr);
    bool internalRemoveContentPane(int index = -1, QString name = "",
                                   QFrame *contentFrame = nullptr,
                                   ContentPane *cpane = nullptr);
    bool internalEnableDisableContentPane(bool disable, int index = -1,
                                          QString header = "",
                                          QFrame *contentPane = nullptr);

    int findContentPaneIndex(QString name = "", QFrame *cframe = nullptr,
                             ContentPane *cpane = nullptr);

    bool checkIndexError(uint index, const QString &errMessage);

protected:
    /**
     * @brief paintEvent Reimplement paintEvent to use stylesheets in derived Widgets
     * @param event
     */
    void paintEvent(__attribute__((unused)) QPaintEvent *event);
};

#endif // QACCORDION_H
