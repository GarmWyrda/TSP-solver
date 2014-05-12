#include "tspParse.h"

void TsplibFile::createSquareMatrix(const int size) {
    for(int i =0; i < size; i++){
        this->EdgeWeghtMatrix.addColumn(0);
        this->EdgeWeghtMatrix.addRow(0);
    }   
}

LoaderFile::LoaderFile() {
}


TsplibFile LoaderFile::load(const string& path) {
    ifstream file(path, ifstream::in);
    string line, Keyword, valueKey;
    char delimiter = ':';
    int sizeLine;
    TsplibFile newfile;
    if (file.bad() or file.fail()) {
        throw FileException("File not exist");
    }
    while (!file.eof()) {
        getline(file, line);
        boost::to_upper(line);
        boost::algorithm::erase_all(line, " ");
        Keyword = line.substr(0, line.find(delimiter));
        sizeLine = line.size();
        if (Keyword.size() != sizeLine) {
            valueKey = line.substr(line.find(delimiter) + 1, sizeLine);
            if (Keyword.compare("NAME") == 0) {
                newfile.SetName(valueKey);
            } else if (Keyword.compare("TYPE") == 0) {
                if ((valueKey.compare("TSP") == 0) or (valueKey.compare("ATSP") == 0)) {
                    newfile.SetType(valueKey);
                } else {
                    string error = "Type ";
                    error += valueKey;
                    error += " not implement";
                    throw FileException(error);
                }
            } else if (Keyword.compare("COMMENT") == 0) {
            } else if (Keyword.compare("DIMENSION") == 0) {
                newfile.SetDimmension(valueKey);
            } else if (Keyword.compare("EDGE_WEIGHT_TYPE") == 0) {
                if (valueKey.compare("EXPLICIT") == 0) {
                    newfile.SetEdge_weight_type(valueKey);
                } else {
                    string error = "Edge weight type : ";
                    error += valueKey;
                    error += " not implement";
                    throw FileException(error);
                }
            } else if (Keyword.compare("EDGE_WEIGHT_FORMAT") == 0) {
                if (valueKey.compare("FUNCTION") == 0) {
                    string error = "Edge weight format : ";
                    error += valueKey;
                    error += " not implement";
                    throw FileException(error);
                } else {
                    newfile.SetEdge_data_format(valueKey);
                }
            } else if (Keyword.compare("NODE_COORD_TYPE") == 0) {
                newfile.SetNode_coord_type(valueKey);
            } else if (Keyword.compare("DISPLAY_DATA_TYPE") == 0) {
                newfile.SetDisplay_data_type(valueKey);
            } else {
                string error = "KeyWord : ";
                error += Keyword;
                error += " unknow";
                throw FileException(error);
            }
        } else if (Keyword.compare("EDGE_WEIGHT_SECTION") == 0) {
            LoaderFile load;
            load.readEdgeSection(file, newfile.GetEdge_data_format(), newfile.GetDimension(), newfile);

        }

    }
    file.close();
    return newfile;
}

void LoaderFile::setFulllMatrix(ifstream& file, const int& size, TsplibFile& tsplibfile) {
    string line;
    getline(file, line);
    typedef vector< string > find_vector_type;
    find_vector_type numbers;
    int i, j, value;
    i = j = 0;
    tsplibfile.createSquareMatrix(size);
    while (!(file.eof()) and (this->is_number(line) or (line[0] == ' '))){
        j = 0;
        while (j < size) {
            boost::split(numbers, line, boost::is_any_of(" "));
            for (auto& val : numbers) {
                if (val != "") {
                    if (i != j) {
                        value = atoi(val.c_str());
                        tsplibfile.setEdgeValue(i, j, value);
                    }
                    j++;
                }
            }
            getline(file, line);
        }
        i++;
    }
}


void LoaderFile::set(ifstream& file, const int& size, TsplibFile& tsplibfile) {
    string line;
    getline(file, line);
    typedef vector< string > find_vector_type;
    find_vector_type numbers;
    int i, j, value;
    i = j = 0;
    tsplibfile.createSquareMatrix(size);
    while (!(file.eof()) and (this->is_number(line) or (line[0] == ' '))){
        boost::split(numbers, line, boost::is_any_of(" "));
        j = 0;
        for (auto& val : numbers) {
            if (val != "") {
                while (tsplibfile.getMatrix().getValue(i, j) != -1) {
                    j++;
                }
                if (i == j) {
                    j++;
                }
                if (tsplibfile.getMatrix().getValue(i, j) == -1) {
                    value = atoi(val.c_str());
                    tsplibfile.setEdgeValue(i, j, value);
                    tsplibfile.setEdgeValue(j, i, value);
                }
                j++;
            }
        }
        i++;
        getline(file, line);
    }
}



void LoaderFile::setDiag(ifstream& file, const int& size, TsplibFile& tsplibfile) {
    string line;
    typedef vector< string > find_vector_type;
    find_vector_type numbers;
    int i, j, value;
    getline(file, line);
    i = j = 0;
    tsplibfile.createSquareMatrix(size);
    while (!(file.eof()) and (this->is_number(line) or (line[0] == ' '))){
        boost::split(numbers, line, boost::is_any_of(" "));
        
        for (auto& val : numbers) {
            if (val.size() != 0) {
                while (tsplibfile.getMatrix().getValue(i, j) != -1) {
                    j++;
                }
                if (val.compare("0") == 0) {
                    i++;
                    j = 0;
                } else {
                    if (i == j) {
                        j++;
                    }
                    if (tsplibfile.getMatrix().getValue(i, j) == -1) {
                        value = atoi(val.c_str());
                        tsplibfile.setEdgeValue(i, j, value);
                        tsplibfile.setEdgeValue(j, i, value);
                    }
                    j++;
                }
            }
        }
        getline(file, line);
    }
}

bool LoaderFile::readEdgeSection(ifstream& file, const string& format, const string& dim, TsplibFile& tsplibfile) {
    int size = atoi(dim.c_str());
    if (size <= 0) {
        throw FileException("Bad dim in tsp file");
    }
    if (format.compare("FULL_MATRIX") == 0) {
        this->setFulllMatrix(file, size, tsplibfile);
        //function fullMatrix
    } else if (format.compare("UPPER_ROW") == 0) {
        this->set(file, size, tsplibfile);
        //function upper_row
    } else if (format.compare("LOWER_ROW") == 0) {
        this->set(file, size, tsplibfile);
        //function lower_row (upper_row en commencant de la fin)
    } else if (format.compare("UPPER_DIAG_ROW") == 0) {
        this->setDiag(file, size, tsplibfile);
        //function upper_diag_row
    } else if (format.compare("LOWER_DIAG_ROW") == 0) {
        this->setDiag(file, size, tsplibfile);
        //function LOWER_diag_row
    } else if (format.compare("UPPER_COL") == 0) {
        this->set(file, size, tsplibfile);
        //function upper_col
    } else if (format.compare("LOWER_COL") == 0) {
        this->set(file, size, tsplibfile);
        //function LOWER_COL
    } else if (format.compare("UPPER_DIAG_COL") == 0) {
        this->setDiag(file, size, tsplibfile);
        //function upper_diag_col
    } else if (format.compare("LOWER_DIAG_COL") == 0) {
        this->setDiag(file, size, tsplibfile);
        //function lower_diag_col
    } else {
        throw FileException("Edge format unknow");
    }
}
