#ifndef FILE_REPOSITORY_H
#define FILE_REPOSITORY_H

class FileRepository {
  public:
    FileRepository() = default;
    virtual ~FileRepository() = default;
    virtual File get(std::string dir, std::string filename) = 0;
    virtual void save(std::string dir, File file) = 0;
};

#endif
