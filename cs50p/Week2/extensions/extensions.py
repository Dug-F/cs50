def main():
    # get filename from user
    filename = input("File name: ")
    print(f"{mime_type(filename.lower().rstrip())}")


def mime_type(filename):
    # split filename to get final extension
    extensions = filename.split('.')
    # if no extension in filename
    if len(extensions) < 2:
        return "application/octet-stream"

    # define extension to mime type conversion
    mime_types = {
        "gif": "image/gif",
        "jpg": "image/jpeg",
        "jpeg": "image/jpeg",
        "png": "image/png",
        "pdf": "application/pdf",
        "txt": "text/plain",
        "zip": "application/zip"
    }

    # return mime type for extension
    return mime_types.get(extensions[-1], "application/octet-stream")



if __name__ == "__main__":
    main()