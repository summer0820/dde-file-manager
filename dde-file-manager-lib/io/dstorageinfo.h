/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     zccrs <zccrs@live.com>
 *
 * Maintainer: zccrs <zhangjide@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DSTORAGEINFO_H
#define DSTORAGEINFO_H

#include <dfmglobal.h>

#include <QStorageInfo>

DFM_BEGIN_NAMESPACE

class DStorageInfoPrivate;
class DStorageInfo : public QStorageInfo
{
    Q_DECLARE_PRIVATE(DStorageInfo)

public:
    enum PathHint {
        FollowSymlink = 0x01,
    };

    Q_DECLARE_FLAGS(PathHints, PathHint)

    DStorageInfo();
    explicit DStorageInfo(const QString &path, PathHints hints = 0);
    explicit DStorageInfo(const QDir &dir, PathHints hints = 0);
    ~DStorageInfo();

    DStorageInfo &operator=(const DStorageInfo &other);
#ifdef Q_COMPILER_RVALUE_REFS
    DStorageInfo &operator=(DStorageInfo &&other) Q_DECL_NOTHROW { swap(other); return *this; }
#endif

    inline void swap(DStorageInfo &other) Q_DECL_NOTHROW
    { qSwap(d_ptr, other.d_ptr); }

    void setPath(const QString &path, PathHints hints = 0);

    QByteArray fileSystemType() const;

    qint64 bytesTotal() const;
    qint64 bytesFree() const;
    qint64 bytesAvailable() const;

    bool isReadOnly() const;

    void refresh();

    static bool inSameDevice(QString path1, QString path2, PathHints hints = 0);
    static bool inSameDevice(const DUrl &url1, const DUrl &url2, PathHints hints = 0);

private:
    QScopedPointer<DStorageInfoPrivate> d_ptr;
};

DFM_END_NAMESPACE

#endif // DSTORAGEINFO_H