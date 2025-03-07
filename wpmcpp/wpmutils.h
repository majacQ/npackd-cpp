#ifndef WPMUTILS_H
#define WPMUTILS_H

#include <windows.h>
#include <time.h>

#include "qstring.h"
#include "qdir.h"
#include "QTime"

#include "job.h"
#include "version.h"

/**
 * Some utility methods.
 */
class WPMUtils
{
private:
    WPMUtils();
public:
    static const char* NPACKD_VERSION;

    /**
     * Converts the value returned by SHFileOperation to an error message.
     *
     * @param res value returned by SHFileOperation
     * @return error message or "", if OK
     */
    static QString getShellFileOperationErrorMessage(int res);

    /**
     * Moves a directory to a recycle bin.
     *
     * @param dir directory
     * @return error message or ""
     */
    static QString moveToRecycleBin(QString dir);

    /**
     * @return true if this program is running on a 64-bit Windows
     */
    static bool is64BitWindows();

    /**
     * Deletes a directory
     *
     * @param job progress for this task
     * @param aDir this directory will be deleted
     */
    static void removeDirectory(Job* job, QDir &aDir);

    /**
     * Uses the Shell's IShellLink and IPersistFile interfaces
     * to create and store a shortcut to the specified object.
     *
     * @return the result of calling the member functions of the interfaces.
     * @param lpszPathObj - address of a buffer containing the path of the object.
     * @param lpszPathLink - address of a buffer containing the path where the
     *      Shell link is to be stored.
     * @param lpszDesc - address of a buffer containing the description of the
     *      Shell link.
     * @param workingDir working directory
     */
    static HRESULT createLink(LPCWSTR lpszPathObj, LPCWSTR lpszPathLink,
            LPCWSTR lpszDesc,
            LPCWSTR workingDir);

    /**
     * Finds the parent directory for a path.
     *
     * @param path a directory
     * @return parent directory without an ending \\
     */
    static QString parentDirectory(const QString& path);

    /**
     * @return directory like "C:\Program Files"
     */
    static QString getProgramFilesDir();

    /**
     * - lower case
     * - replaces / by \
     * - removes \ at the end
     * - replace multiple occurences of \
     *
     * @param path a file/directory path
     * @return normalized path
     */
    static QString normalizePath(const QString& path);

    /**
     * @param commandLine command line
     * @param err error message will be stored here or ""
     * @return parts of the command line
     */
    static QStringList parseCommandLine(const QString& commandLine,
        QString* err);

    /**
     * Checks if a file or a directory is in the list of specified directories
     * or equals to one of this directories.
     *
     * @param file file or directory. The path should be normalized.
     * @param dirs directories. The paths should be normalized
     */
    static bool isUnderOrEquals(const QString& file, const QStringList& dirs);

    /**
     * Validates a GUID
     *
     * @param guid a GUID
     * @return error message or ""
     */
    static QString validateGUID(const QString& guid);

    /**
     * @param type a CSIDL constant like CSIDL_COMMON_PROGRAMS
     * @return directory like
     *     "C:\Documents and Settings\All Users\Start Menu\Programs"
     */
    static QString getShellDir(int type);

    /**
     * Validates an SHA1.
     *
     * @param sha1 a SHA1 value
     * @return an error message or an empty string if SHA1 is a valid SHA1
     */
    static QString validateSHA1(const QString& sha1);

    /**
     * Validates a full package name.
     *
     * @param n a package name
     * @return an error message or an empty string if n is a valid package name.
     */
    static QString validateFullPackageName(const QString& n);

    /**
     * @param name invalid full package name
     * @return valid package name
     */
    static QString makeValidFullPackageName(const QString& name);

    /**
     * Formats a Windows error message.
     *
     * @param err see GetLastError()
     * @param errMsg the message will be stored her
     */
    static void formatMessage(DWORD err, QString* errMsg);

    /**
     * Checks whether a file is somewhere in a directory (at any level).
     *
     * @param file the file
     * @param dir the directory
     */
    static bool isUnder(const QString& file, const QString& dir);

    /**
     * @return directory where the packages will be installed. Typically
     *     c:\program files\Npackd
     */
    static QString getInstallationDirectory();

    /**
     * see getInstallationDirectory()
     */
    static void setInstallationDirectory(const QString& dir);

    /**
     * @return full paths to files locked because of running processes
     */
    static QStringList getProcessFiles();

    /**
     * Computes SHA1 hash for a file
     *
     * @param filename name of the file
     * @return SHA1 or "" in case of an error or SHA1 in lower case
     */
    static QString sha1(const QString& filename);

    /**
     * Scans all files in a directory and deletes all links (.lnk) to files
     * in another directory.
     *
     * @param dir links to items in this directory (or any subdirectory) will
     *     be deleted
     * @param d this directory will be scanned for .lnk files
     */
    static void deleteShortcuts(const QString& dir, QDir& d);

    /**
     * @param name file name possible containing not allowed characters (like /)
     * @param rep replacement character for invalid characters
     * @return file name with invalid characters replaced by rep
     */
    static QString makeValidFilename(const QString& name, const QChar rep);

    /**
     * Input text from the console.
     *
     * @return entered text
     */
    static QString inputTextConsole();

    /**
     * Output text to the console.
     *
     * @param txt the text
     * @param stdout_ true = stdout, false = stderr
     */
    static void outputTextConsole(const QString& txt, bool stdout_=true);

    /**
     * Is the output redirected?
     *
     * @return true if the output is redirected (e.g. into a file)
     * @param stdout_ true = stdout, false = stderr
     */
    static bool isOutputRedirected(bool stdout_);

    /**
     * @param diff duration
     * @return time
     */
    static QTime durationToTime(time_t diff);

    /**
     * Input a password from the console.
     *
     * @return entered password
     */
    static QString inputPasswordConsole();

    /**
     * Creates a path for a non-existing file/directory based on the start
     * value.
     *
     * @param start start path (e.g. C:\Program Files\Prog 1.0%1). %1 will be
     *     either replaced by "" or by "_2", "_3", ...
     * @return non-existing path based on start
     *     (e.g. C:\Program Files\Prog 1.0_2)
     */
    static QString findNonExistingFile(const QString& start);

    /**
     * Reads a value from the registry.
     *
     * @param hk open key
     * @param var name of the REG_SZ-Variable
     * @return value or "" if an error has occured
     */
    static QString regQueryValue(HKEY hk, const QString& var);

    /**
     * @return directory with the .exe
     */
    static QString getExeDir();

    /**
     * @return C:\Windows
     */
    static QString getWindowsDir();

    /**
     * Finds the path to cmd.exe. Returns 64-bit cmd.exe on 64-bit systems.
     *
     * @return path to cmd.exe
     */
    static QString findCmdExe();

    /**
     * @return GUIDs for installed products (MSI) in lower case
     */
    static QStringList findInstalledMSIProducts();

    /**
     * Finds location of an installed MSI product.
     *
     * @param guid product GUID
     * @param err error message will be stored here
     * @return installation location (C:\Program Files\MyProg)
     */
    static QString getMSIProductLocation(const QString& guid, QString* err);

    /**
     * Returns the value of the specified attribute for the specified MSI
     * product.
     *
     * @param guid product GUID
     * @param attribute INSTALLPROPERTY_PRODUCTNAME for the name etc
     * @param err error message will be stored here
     * @return installation location (C:\Program Files\MyProg)
     */
    static QString getMSIProductAttribute(const QString& guid,
            LPCWSTR attribute, QString* err);

    /**
     * Finds the name of an installed MSI product.
     *
     * @param guid product GUID
     * @param err error message will be stored here
     * @return product name
     */
    static QString getMSIProductName(const QString& guid, QString* err);

    /**
     * Compares 2 file paths.
     *
     * @param patha absolute file path
     * @param pathb absolute file path
     * @return true if paths are equal
     */
    static bool pathEquals(const QString& patha, const QString& pathb);

    /**
     * @return Names and GUIDs for installed products (MSI)
     */
    static QStringList findInstalledMSIProductNames();

    /**
     * @param path .DLL file path
     * @return version number or 0.0 it it cannot be determined
     */
    static Version getDLLVersion(const QString& path);

    /**
     * Changes a system environment variable.
     *
     * @param name name of the variable
     * @param value value of the variable
     * @param expandVars true if REG_EXPAND_SZ should be used instead of REG_SZ
     * @return error message or ""
     */
    static QString setSystemEnvVar(const QString& name, const QString& value,
            bool expandVars=false);

    /**
     * Reads a system environment variable.
     *
     * @param name name of the variable
     * @param err error message will be stored here
     * @return value value of the variable
     */
    static QString getSystemEnvVar(const QString& name, QString* err);

    /**
     * @param text multiline text
     * @return first non-empty line from text
     */
    static QString getFirstLine(const QString& text);

    /**
     * Notifies other Windows applications that an environment entry like "PATH"
     * was changed.
     */
    static void fireEnvChanged();

    static void createMSTask();
};

#endif // WPMUTILS_H
