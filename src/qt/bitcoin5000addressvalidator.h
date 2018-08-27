// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN5000_QT_BITCOIN5000ADDRESSVALIDATOR_H
#define BITCOIN5000_QT_BITCOIN5000ADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class Bitcoin5000AddressEntryValidator : public QValidator {
  Q_OBJECT

public:
  explicit Bitcoin5000AddressEntryValidator(QObject *parent);

  State validate(QString &input, int &pos) const;
};

/** Bitcoin5000 address widget validator, checks for a valid bitcoin5000
 * address.
 */
class Bitcoin5000AddressCheckValidator : public QValidator {
  Q_OBJECT

public:
  explicit Bitcoin5000AddressCheckValidator(QObject *parent);

  State validate(QString &input, int &pos) const;
};

#endif // BITCOIN5000_QT_BITCOIN5000ADDRESSVALIDATOR_H
