#include "freertosgenerator.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <LCD/ccodecreator.h>
#include "pathstorage.h"

FreeRtosGenerator::FreeRtosGenerator(const Display &d): CHGenerator(d)
{
}

QStringList FreeRtosGenerator::getFileNames()
{
    QStringList outFiles;
    outFiles << "fc_u.c" << "iodefines.h";
    return outFiles;
}

int FreeRtosGenerator::createFiles(TextBlock &varBlock, TextBlock &initBlock, QVector<KonProcess> &prBlock){
    this->varBlock = varBlock;
    this->initBlock = initBlock;
    this->prBlock = prBlock;
    translateKonToC();
    if(errorList.count()==0) {
        createFcuC();
        createIoDefinesH();
    }
    return 1;
}

void FreeRtosGenerator::scanMatchbox()
{
    for(int i=0;i<prBlock.count();i++) {
        curPrNum = prBlock[i].getNum();
        int sitCount = prBlock[i].getSituations().count();
        for(int j=0;j<sitCount;j++) {
            curSitNum = prBlock[i].getSituation(j).getSitNum();
            curSitSpeed = prBlock[i].getSituation(j).getPeriod();
            foreach(QString str,prBlock[i].getSituation(j).getText()){
                QRegExp in("IN(\\d+)(?!_)");
                int pos=0;
                while((pos=in.indexIn(str,pos))!=-1){
                    // except DIN
                    if(pos){
                        if(str[pos-1]=='D') {
                            pos+=in.matchedLength();
                            break;
                        }
                    }
                    int modNum = in.cap(1).toInt();
                    if(modNum>=4){
                        // add new module in list
                        bool isNewMod = true;
                        ModuleIO mod(ModuleIO::MDI);
                        mod.setNetAddress("IN"+QString::number(modNum));
                        ModuleIO::speedPriority speed=ModuleIO::LOW_PRIORITY;
                        if(curSitSpeed==1) speed = ModuleIO::HIGH_PRIORITY;
                        else if(curSitSpeed<100) speed = ModuleIO::NORMAL_PRIORITY;
                        mod.setSpeed(speed);
                        for(int i=0;i<modIo.count();i++){
                            if(modIo[i].getNetAddress()==mod.getNetAddress()){
                                isNewMod = false;
                                // if new speed is higher update
                                if(mod.getSpeed()<modIo[i].getSpeed()) modIo[i].setSpeed(mod.getSpeed());
                            }
                        }
                        if(isNewMod) modIo+=mod;
                    }
                    pos+=in.matchedLength();
                }

                QRegExp out("OUT(\\d+)(?!_)");
                pos=0;
                while((pos=out.indexIn(str,pos))!=-1){
                    // except DOUT
                    if(pos){
                        if(str[pos-1]=='D') {
                            pos+=out.matchedLength();
                            break;
                        }
                    }
                    int modNum = out.cap(1).toInt();
                    if(modNum>=4){
                        // add new module in list
                        bool isNewMod = true;
                        ModuleIO mod(ModuleIO::MDO);
                        mod.setNetAddress("OUT"+QString::number(modNum));
                        ModuleIO::speedPriority speed=ModuleIO::LOW_PRIORITY;
                        if(curSitSpeed==1) speed = ModuleIO::HIGH_PRIORITY;
                        else if(curSitSpeed<100) speed = ModuleIO::NORMAL_PRIORITY;
                        mod.setSpeed(speed);
                        for(int i=0;i<modIo.count();i++){
                            if(modIo[i].getNetAddress()==mod.getNetAddress()){
                                isNewMod = false;
                                // if new speed is higher update
                                if(mod.getSpeed()<modIo[i].getSpeed()) modIo[i].setSpeed(mod.getSpeed());
                            }
                        }
                        if(isNewMod) modIo+=mod;
                    }
                    pos+=out.matchedLength();
                }

                QRegExp adc("AD[CH](\\d+)(?!_)");
                pos=0;
                while((pos=adc.indexIn(str,pos))!=-1){
                    int modNum = adc.cap(1).toInt();
                    if(modNum>=9){
                        // add new module in list
                        bool isNewMod = true;
                        ModuleIO mod(ModuleIO::MAI);
                        mod.setNetAddress("ADC"+QString::number(modNum));
                        ModuleIO::speedPriority speed=ModuleIO::LOW_PRIORITY;
                        if(curSitSpeed==1) speed = ModuleIO::HIGH_PRIORITY;
                        else if(curSitSpeed<100) speed = ModuleIO::NORMAL_PRIORITY;
                        mod.setSpeed(speed);
                        for(int i=0;i<modIo.count();i++){
                            if(modIo[i].getNetAddress()==mod.getNetAddress()){
                                isNewMod = false;
                                // if new speed is higher update
                                if(mod.getSpeed()<modIo[i].getSpeed()) modIo[i].setSpeed(mod.getSpeed());
                            }
                        }
                        if(isNewMod) modIo+=mod;
                    }
                    pos+=adc.matchedLength();
                }

                QRegExp dac("DAC(\\d+)(?!_)");
                pos=0;
                while((pos=dac.indexIn(str,pos))!=-1){
                    int modNum = dac.cap(1).toInt();
                    if(modNum>=5){
                        // add new module in list
                        bool isNewMod = true;
                        ModuleIO mod(ModuleIO::MAO);
                        mod.setNetAddress("DAC"+QString::number(modNum));
                        ModuleIO::speedPriority speed=ModuleIO::LOW_PRIORITY;
                        if(curSitSpeed==1) speed = ModuleIO::HIGH_PRIORITY;
                        else if(curSitSpeed<100) speed = ModuleIO::NORMAL_PRIORITY;
                        mod.setSpeed(speed);
                        for(int i=0;i<modIo.count();i++){
                            if(modIo[i].getNetAddress()==mod.getNetAddress()){
                                isNewMod = false;
                                // if new speed is higher update
                                if(mod.getSpeed()<modIo[i].getSpeed()) modIo[i].setSpeed(mod.getSpeed());
                            }
                        }
                        if(isNewMod) modIo+=mod;
                    }
                    pos+=dac.matchedLength();
                }
            }
        }
    }
}

void FreeRtosGenerator::translateKonToC()
{
    QVector<int> sitPeriod = {1,5,10,100,1000};
    translateTextBlock(varBlock.getText(),varBlock.getKonNums());
    translateTextBlock(initBlock.getText(),initBlock.getKonNums());

    scanMatchbox();

    for(int i=0;i<prBlock.count();i++) {
        curPrNum = prBlock[i].getNum();
        int sitCount = prBlock[i].getSituations().count();
        for(int j=0;j<sitCount;j++) {
            curSitNum = prBlock[i].getSituation(j).getSitNum();
            curSitSpeed = prBlock[i].getSituation(j).getPeriod();
            if(!sitPeriod.contains(curSitSpeed)) errorList+="Некорректный период ситуации. Процесс " + QString::number(curPrNum) + ", ситуация " + QString::number(curSitNum);
            else translateTextBlock(prBlock[i].getSituation(j).getText(),prBlock[i].getSituation(j).getKonNums());
        }
    }
}

void FreeRtosGenerator::createIoDefinesH()
{
    //QString path = QCoreApplication::applicationDirPath();
    QDir dir(PathStorage::getSrcDir());
    if(!dir.exists()) {dir.mkdir(".");}
    QFile file(dir.path()+"/iodefines.h");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        errorList+="Ошибка создания " + file.fileName();
        return;
    }

    QTextStream out(&file);

    for(int i=0;i<modIo.count();i++) {
        int netAddr = modIo[i].getNetAddress();
        if(netAddr>0){
            if(netAddr<=ModuleIO::getInEnd()) {
                out << "#define IN" << QString::number(netAddr-ModuleIO::getInStart()+4) << "   IN[" << QString::number(netAddr-ModuleIO::getInStart()) << "]\n";
            }else if(netAddr<=ModuleIO::getOutEnd()) {
                out << "#define OUT" << QString::number(netAddr-ModuleIO::getOutStart()+4) << "   OUT[" << QString::number(netAddr-ModuleIO::getOutStart()) << "]\n";
            }else if(netAddr<=ModuleIO::getAdcEnd()) {
                for(int j=0;j<4;j++) {
                    out << "#define ADC" << QString::number((netAddr-ModuleIO::getAdcStart())*4+9+j) << " _ADC.D" << QString::number(j+1) << "[" << QString::number(netAddr-ModuleIO::getAdcStart()) << "]\n";
                    out << "#define ADH" << QString::number((netAddr-ModuleIO::getAdcStart())*4+9+j) << " (_ADC.D" << QString::number(j+1) << "[" << QString::number(netAddr-ModuleIO::getAdcStart()) << "]>>8)\n";
                }
            }else {
                for(int j=0;j<2;j++) {
                    out << "#define DAC" << QString::number((netAddr-ModuleIO::getDacStart())*2+5+j) << " _DAC.D" << QString::number(j+1) << "[" << QString::number(netAddr-ModuleIO::getDacStart()) << "]\n";
                }
            }
        }
    }
    QFile::remove(PathStorage::getBuildDir()+"/iodefines.h");
    file.copy(PathStorage::getBuildDir()+"/iodefines.h");

    file.close();
}

void FreeRtosGenerator::translateIO(QString &str, int konNum)
{
    bool errExp = false;
    QRegExp adcExp("ADC(\\d+)");
    int pos=0;
    while((pos = adcExp.indexIn(str,pos))!=-1) {
        int adcNum = adcExp.cap(1).toInt();
        if((adcNum>=1)&&(adcNum<=8)) {
            str.remove(pos,adcExp.matchedLength());
            QString newExp = "_Sys_ADC["+QString::number(adcNum-1)+"]";
            str.insert(pos,newExp);
        }
        pos += adcExp.matchedLength();
    }

    errExp = false;
    QRegExp inExp("#IN(\\d+).(\\d+)");
    pos=0;
    while((pos = inExp.indexIn(str,pos))!=-1) {
        int inNum = inExp.cap(1).toInt();
        int bitNum = inExp.cap(2).toInt();
        if((inNum>=0)&&(inNum<4+32)) {
            if((bitNum>=0)&&(bitNum<8)) {
                str.remove(pos,inExp.matchedLength());
                if(inNum<4) {
                    QString newExp = "(*(iostruct*)&_Sys_IN["+QString::number(inNum)+"]).bit"+QString::number(bitNum);
                    str.insert(pos,newExp);
                }else {
                    QString newExp = "(*(iostruct*)&IN["+QString::number(inNum-4)+"]).bit"+QString::number(bitNum);
                    str.insert(pos,newExp);
                }
            }else errExp=true;
        }else errExp=true;
        if(errExp) errorList+="Некорректное выражение: " + inExp.cap() + ". Строка " + QString::number(konNum);
        pos += inExp.matchedLength();
    }

    errExp = false;
    QRegExp dinExp("#DIN(\\d+).(\\d+)");
    pos=0;
    while((pos = dinExp.indexIn(str,pos))!=-1) {
        int dinNum = dinExp.cap(1).toInt();
        int bitNum = dinExp.cap(2).toInt();
        if((dinNum>=4)&&(dinNum<6)) {
            if((bitNum>=0)&&(bitNum<8)) {
                str.remove(pos,dinExp.matchedLength());
                QString newExp = "(*(iostruct*)&_Sys_IN["+QString::number(dinNum)+"]).bit"+QString::number(bitNum);
                str.insert(pos,newExp);
            }else errExp=true;
        }else errExp=true;
        if(errExp) errorList+="Некорректное выражение: " + dinExp.cap() + ". Строка " + QString::number(konNum);
        pos += dinExp.matchedLength();
    }

    errExp = false;
    QRegExp outExp("#OUT(\\d+).(\\d+)");
    pos=0;
    while((pos = outExp.indexIn(str,pos))!=-1) {
        int outNum = outExp.cap(1).toInt();
        int bitNum = outExp.cap(2).toInt();
        if((outNum>=0)&&(outNum<4+32)) {
            if((bitNum>=0)&&(bitNum<8)) {
                str.remove(pos,outExp.matchedLength());
                if(outNum<4) {
                    QString newExp = "(*(iostruct*)&_Sys_OUT["+QString::number(outNum)+"]).bit"+QString::number(bitNum);
                    str.insert(pos,newExp);
                }else {
                    QString newExp = "(*(iostruct*)&OUT["+QString::number(outNum-4)+"]).bit"+QString::number(bitNum);
                    str.insert(pos,newExp);
                }
            }else errExp=true;
        }else errExp=true;
        if(errExp) errorList+="Некорректное выражение: " + outExp.cap() + ". Строка " + QString::number(konNum);
        pos += outExp.matchedLength();
    }

    errExp = false;
    QRegExp doutExp("#DOUT(\\d+).(\\d+)");
    pos=0;
    while((pos = doutExp.indexIn(str,pos))!=-1) {
        int doutNum = doutExp.cap(1).toInt();
        int bitNum = doutExp.cap(2).toInt();
        if((doutNum>=4)&&(doutNum<6)) {
            if((bitNum>=0)&&(bitNum<8)) {
                str.remove(pos,doutExp.matchedLength());
                QString newExp = "(*(iostruct*)&_Sys_OUT["+QString::number(doutNum)+"]).bit"+QString::number(bitNum);
                str.insert(pos,newExp);
            }else errExp=true;
        }else errExp=true;
        if(errExp) errorList+="Некорректное выражение: " + doutExp.cap() + ". Строка " + QString::number(konNum);
        pos += doutExp.matchedLength();
    }
}

void FreeRtosGenerator::translateSitJump(QString &str, int konNum)
{
    QRegExp repExp("\\s*#/R;");
    int pos = 0;
    while((pos = repExp.indexIn(str,pos))!=-1) {
        str.remove(pos,repExp.matchedLength());
        QString newExp = "_Sys4x_p"+QString::number(curPrNum)+".DELAY=0;break;";
        str.insert(pos,newExp);
        pos += repExp.matchedLength();
    }
    QRegExp repPauseExp("\\s*#/(\\d+\\.\\d+)/R;");
    pos = 0;
    while((pos = repPauseExp.indexIn(str,pos))!=-1) {
        int pauseMs = repPauseExp.cap(1).toDouble()*1000;
        str.remove(pos,repPauseExp.matchedLength());
        QString newExp = "_Sys4x_p"+QString::number(curPrNum)+".DELAY="+QString::number(pauseMs)+";break;";
        str.insert(pos,newExp);
        pos += repPauseExp.matchedLength();
    }
    QRegExp jumpExp("\\s*#/s(\\d+);");
    pos = 0;
    while((pos = jumpExp.indexIn(str,pos))!=-1) {
        int sitNum = jumpExp.cap(1).toInt();
        // check number of new situation
        bool isNumCorrect = false;
        for(int i=0;i<prBlock.count();i++) {
            if(prBlock[i].getNum()==curPrNum) {
                for(int j=0;j<prBlock[i].getSituations().count();j++) {
                    if(sitNum==prBlock[i].getSituation(j).getSitNum()) {
                        isNumCorrect = true;
                        break;
                    }
                }
            }
            if(isNumCorrect) break;
        }
        if(isNumCorrect) {
            str.remove(pos,jumpExp.matchedLength());
            QString newExp = "_Sys4x_p"+QString::number(curPrNum)+".NEXT="+QString::number(sitNum)+";";
            newExp += "_Sys4x_p"+QString::number(curPrNum)+".DELAY=0;break;";
            str.insert(pos,newExp);
        }else {
            errorList += "Отсутствует ситуация "+QString::number(sitNum)+" в процессе " + QString::number(curPrNum) + ". Строка " + QString::number(konNum);
        }
        pos += jumpExp.matchedLength();
    }

    QRegExp jumpPauseExp("\\s*#/(\\d+.\\d+)/s(\\d+);");
    pos = 0;
    while((pos = jumpPauseExp.indexIn(str,pos))!=-1) {
        int pauseMs = jumpPauseExp.cap(1).toDouble()*1000;
        int sitNum = jumpPauseExp.cap(2).toInt();
        // check number of new situation
        bool isNumCorrect = false;
        for(int i=0;i<prBlock.count();i++) {
            if(prBlock[i].getNum()==curPrNum) {
                for(int j=0;j<prBlock[i].getSituations().count();j++) {
                    if(sitNum==prBlock[i].getSituation(j).getSitNum()) {
                        isNumCorrect = true;
                        break;
                    }
                }
            }
            if(isNumCorrect) break;
        }
        if(isNumCorrect) {
            str.remove(pos,jumpPauseExp.matchedLength());
            QString newExp = "_Sys4x_p"+QString::number(curPrNum)+".NEXT="+QString::number(sitNum)+";";
            newExp += "_Sys4x_p"+QString::number(curPrNum)+".DELAY="+QString::number(pauseMs)+";break;";
            str.insert(pos,newExp);
        }else {
            errorList += "Отсутствует ситуация "+QString::number(sitNum)+" в процессе " + QString::number(curPrNum) + ". Строка " + QString::number(konNum);
        }
        pos += jumpPauseExp.matchedLength();
    }
}

void FreeRtosGenerator::translateStartStopProc(QString &str, int konNum)
{
    QRegExp startExp("\\s*#STARTp(\\d+);");
    int pos = 0;
    while((pos = startExp.indexIn(str,pos))!=-1) {
        int prNum = startExp.cap(1).toInt();
        bool hasProgThisProcNum = false;
        for(int i=0;i<prBlock.count();i++){
            if(prBlock[i].getNum()==prNum){
                str.remove(pos,startExp.matchedLength());
                if(prBlock[i].getSituations().count()){
                    hasProgThisProcNum = true;
                    QString newExp = "  {_Sys4x_p"+QString::number(prNum)+".SIT=";
                    newExp += "_Sys4x_p"+QString::number(prNum)+".NEXT=";
                    newExp += QString::number(prBlock[i].getSituation(0).getSitNum())+";";
                    newExp += "_Sys4x_p"+QString::number(prNum)+".DELAY=0;}";
                    str.insert(pos,newExp);
                }
                break;
            }
        }
        if(hasProgThisProcNum==false) errorList+="Ошибка запуска процесса " + QString::number(prNum) + ". Строка " + QString::number(konNum) + ".";
        pos += startExp.matchedLength();
    }
    QRegExp stopExp("\\s*#STOPp(\\d+);");
    pos = 0;
    while((pos = stopExp.indexIn(str,pos))!=-1) {
        int prNum = stopExp.cap(1).toInt();
        bool hasProgThisProcNum = false;
        for(int i=0;i<prBlock.count();i++){
            if(prBlock[i].getNum()==prNum){
                str.remove(pos,stopExp.matchedLength());
                hasProgThisProcNum = true;
                QString newExp = "{_Sys4x_p"+QString::number(prNum)+".DELAY=-1;}";
                str.insert(pos,newExp);
                break;
            }
        }
        if(hasProgThisProcNum==false) errorList+="Ошибка остановки процесса " + QString::number(prNum) + ". Строка " + QString::number(konNum) + ".";
        pos += stopExp.matchedLength();
    }
}

void FreeRtosGenerator::translateTextBlock(QStringList &strList, QVector<int> &konStrNum)
{
    for(int i=0;i<strList.count();i++) {
        int konNum=0;
        if(i<konStrNum.count()) konNum = konStrNum[i];
        translateIO(strList[i],konNum);
        translateSitJump(strList[i],konNum);
        translateStartStopProc(strList[i],konNum);
    }
}

void FreeRtosGenerator::printProcess(QTextStream &out, int procId,int period)
{
    bool hasItPeriod = false;
    for(int j=0;j<prBlock[procId].getSituations().count();j++){
        if(prBlock[procId].getSituation(j).getPeriod()==period) {hasItPeriod=true;break;}
    }
    if(hasItPeriod){
        out << "        if(_Sys4x_p"+QString::number(prBlock[procId].getNum())+".DELAY == 0 ){\n";
        out << "            _Sys4x_p"+QString::number(prBlock[procId].getNum())+".SIT=_Sys4x_p"+QString::number(prBlock[procId].getNum())+".NEXT;\n";
        out << "            switch(_Sys4x_p"+QString::number(prBlock[procId].getNum())+".SIT){\n";
        for(int j=0;j<prBlock[procId].getSituations().count();j++) {
            if(prBlock[procId].getSituation(j).getPeriod()==period) {
                out << "            case "+QString::number(prBlock[procId].getSituation(j).getSitNum())+":\n";
                foreach (QString str, prBlock[procId].getSituation(j).getText()) {
                    out << "                " << str << "\n";
                }
                out << "                break;\n";
            }
        }
        out << "            }\n";
        out << "        }\n";
    }
}

void FreeRtosGenerator::createFcuC()
{
    QDir dir(PathStorage::getSrcDir());
    if(!dir.exists()) {dir.mkdir(".");}
    QFile file(dir.path()+"/fc_u.c");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        errorList+="Ошибка создания " + file.fileName();
        return;
    }

    QTextStream out(&file);

    out << "#include \"fc_u.h\"\n";
    out << "#include \"additional.h\"\n";
    out << "extern unsigned long sd_fl;\n";
    out << "const unsigned short S4_max = " + QString::number(lcd.getVisibleSubStrCount(lcd.getStrCount()-1)) + ";\n";

    out << "\n";

    // matchbox defenition


    if(modIo.count()) {
        out << "const unsigned char mod_table[]={\n";
        foreach (ModuleIO mod, modIo) {
           if(mod.getNetAddress()>0) {
               out << QString::number(mod.getNetAddress()) << ", 0,\n";
           }
        }
        out << "0};\n";
    }else {
        out << "const unsigned char mod_table[]={0x00};\n";
    }
    out << "\n";

    for(int i=0;i<varBlock.getText().count();i++) {
        out << varBlock.getText().at(i) + "\n";
    }

    out << "struct process\n";
    out << "{\n";
    out << "    unsigned long DELAY;\n";
    out << "    unsigned int SIT;\n";
    out << "    unsigned int NEXT;\n";
    out << "}";
    for(int i=0;i<prBlock.count();i++) {
        out << "_Sys4x_p" << prBlock[i].getNum();
        if(i!=prBlock.count()-1) out << ",";
        else out << ";\n";
    }
    out << "\n";
    out << "void R100Task( void *pvParameters )\n";
    out << "{\n";
    out << "    portTickType xLastExecutionTime;\n";
    out << "    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);\n";
    out << "    IWDG_SetPrescaler(IWDG_Prescaler_64); // IWDG counter clock: 40KHz(LSI) / 64  (1.6 ms)\n";
    out << "    IWDG_SetReload(150);\n";
    out << "    IWDG_ReloadCounter();\n";
    out << "    IWDG_Enable();\n";
    out << "    xLastExecutionTime = xTaskGetTickCount();\n";
    out << "    for( ;; )\n";
    out << "    {\n";
    for(int i=0;i<prBlock.count();i++) {
        printProcess(out,i,100);
    }
    out << "        IWDG_ReloadCounter();\n";
    out << "        r100++;\n";
    out << "        vTaskDelayUntil( &xLastExecutionTime, R100_DELAY );\n";
    out << "    }\n";
    out << "}\n";
    out << "\n";

    out << "void R1Task( void *pvParameters )\n";
    out << "{\n";
    out << "    portTickType xLastExecutionTime;\n";
    out << "    xLastExecutionTime = xTaskGetTickCount();\n";
    out << "    for( ;; )\n";
    out << "    {\n";
    for(int i=0;i<prBlock.count();i++) {
        out << "        if(_Sys4x_p"+QString::number(prBlock[i].getNum())+".DELAY>0) _Sys4x_p"+QString::number(prBlock[i].getNum())+".DELAY--;\n";
    }
    out << "\n";
    for(int i=0;i<prBlock.count();i++) {
        printProcess(out,i,1);
    }
    out << "        r1++;\n";
    out << "        vTaskDelayUntil( &xLastExecutionTime, R1_DELAY );\n";
    out << "    }\n";
    out << "}\n";
    out << "\n";

    out << "void R5Task( void *pvParameters )\n";
    out << "{\n";
    out << "    portTickType xLastExecutionTime;\n";
    out << "    xLastExecutionTime = xTaskGetTickCount();\n";
    out << "    for( ;; )\n";
    out << "    {\n";
    for(int i=0;i<prBlock.count();i++) {
        printProcess(out,i,5);
    }
    out << "        r5++;\n";
    out << "        vTaskDelayUntil( &xLastExecutionTime, R5_DELAY );\n";
    out << "    }\n";
    out << "}\n";
    out << "\n";

    out << "void R10Task( void *pvParameters )\n";
    out << "{\n";
    out << "    portTickType xLastExecutionTime;\n";
    out << "    xLastExecutionTime = xTaskGetTickCount();\n";
    out << "    for( ;; )\n";
    out << "    {\n";
    for(int i=0;i<prBlock.count();i++) {
        printProcess(out,i,10);
    }
    out << "        r10++;\n";
    out << "        vTaskDelayUntil( &xLastExecutionTime, R10_DELAY );\n";
    out << "    }\n";
    out << "}\n";
    out << "\n";

    out << "void R1000Task( void *pvParameters )\n";
    out << "{\n";
    out << "    portTickType xLastExecutionTime;\n";
    out << "    xLastExecutionTime = xTaskGetTickCount();\n";
    out << "    for( ;; )\n";
    out << "    {\n";
    for(int i=0;i<prBlock.count();i++) {
        printProcess(out,i,1000);
    }
    out << "        r1000++;\n";
    out << "        vTaskDelayUntil( &xLastExecutionTime, R1000_DELAY );\n";
    out << "    }\n";
    out << "}\n";
    out << "\n";

    out << "void Relkon_init()\n";
    out << "{\n";
    for(int i=0;i<initBlock.getText().count();i++) {
        out << "    " << initBlock.getText().at(i) << "\n";
    }
    out << "}\n";

    QStringList pultData = CCodeCreator::getText(lcd);

    foreach (QString str, pultData) {
       out << str;
    }

    /*out << "\n";
    out << "const unsigned char str1[][20] = {{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}};\n";
    out << "const unsigned char str2[][20] = {{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}};\n";
    out << "const unsigned char str3[][20] = {{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}};\n";
    out << "const unsigned char str4[][20] = {{0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20}};\n";
    out << "\n";
    out << "void print_var(void)\n";
    out << "{\n";
    out << "    \n";
    out << "}\n";*/


    file.close();
}
