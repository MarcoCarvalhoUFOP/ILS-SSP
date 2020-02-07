
my_boxplot <-function()
{
  #   
  #   #Tabela A
  #   
  #   data_a <- data.frame(Proposto = c(17, 16.83, 21.80, 23.07, 22.08, 22.10, 28.20, 27.92, 26.61),
  #                        CS_BRKGA = c(17, 16.83, 21.80, 23.07, 22.08, 22.10, 28.20, 27.92, 26.61))
  #   
  #   time_a <- data.frame(Proposto = c(0.08, 0.10, 0.08, 0.17, 0.14, 0.06, 0.19, 0.23, 0.17),
  #                        CS_BRKGA = c(0.98, 1.03, 1.30, 1.49, 1.34, 1.60, 1.70, 1.62, 1.47))
  #   boxplot(data_a,
  #           ylab="Número de Trocas", xlab ="Método",
  #           main=toupper("Número de Trocas - Grupo A"))
  #   
  #   boxplot(time_a,
  #           ylab="Tempo (segundos)", xlab ="Método",
  #           main=toupper("Tempo Computacional - Grupo A"))
  #   
  #   
  #   
  #   #Tabela B
  #   
  #   data_b <- data.frame(Proposto = c(17.20, 17.37, 22.40, 24.17, 22.60, 22.40, 28.77, 29.74, 27.19),
  #                        CS_BRKGA = c(17.20, 17.37, 22.40, 24.17, 22.60, 22.40, 28.77, 29.74, 27.19))
  #   
  #   time_b <- data.frame(Proposto = c(0.11, 0.16, 0.13, 0.26, 0.24, 0.10, 0.27, 0.43, 0.29),
  #                        CS_BRKGA = c(2.72, 3.15, 3.13, 3.92, 3.99, 4.08, 5.08, 5.10, 5.26))
  #   boxplot(data_b,
  #           ylab="Número de Trocas", xlab ="Método",
  #           main=toupper("Número de Trocas - Grupo B"))
  #   
  #   boxplot(time_b,
  #           ylab="Tempo (segundos)", xlab ="Método",
  #           main=toupper("Tempo Computacional - Grupo B"))
  #   
  #   
  #   
  #   #Tabela C
  #   
  #   data_c <- data.frame(Proposto = c(21.60, 19.80, 25.60, 28.33, 25.52, 32.50, 35.07, 34.07, 29.66),
  #                        CS_BRKGA = c(21.60, 19.80, 25.60, 28.33, 25.52, 32.50, 35.07, 34.07, 29.66))
  #   
  #   time_c <- data.frame(Proposto = c(0.76, 1.20, 0.91, 1.84, 2.00, 0.92, 2.20, 3.33, 2.47),
  #                        CS_BRKGA = c(5.31, 7.10, 7.26, 8.93, 9.61, 9.30, 13.52, 13.63, 13.82))
  #   boxplot(data_c,
  #           ylab="Número de Trocas", xlab ="Método",
  #           main=toupper("Número de Trocas - Grupo c"))
  #   
  #   boxplot(time_c,
  #           ylab="Tempo (segundos)", xlab ="Método",
  #           main=toupper("Tempo Computacional - Grupo c"))
  #   
  #   
  #   
  #   #Tabela D
  #   
  #   data_c <- data.frame(Proposto = c(25.90, 18.20, 29.30, 20.60, 21.67, 35.10, 25.40, 36.25, 26.15, 15.90, 21.60, 22.60, 26.60, 25.00, 25.50),
  #                        CS_BRKGA = c(26.10, 18.20, 29.30, 20.60, 21.67, 35.10, 25.40, 36.25, 26.15, 15.90, 21.60, 22.60, 26.60, 25.00, 25.50))
  #   
  #   time_c <- data.frame(Proposto = c(2.10, 3.39, 2.61, 3.93, 4.56, 2.69, 4.75, 9.59, 4.75, 6.56, 12.96, 13.41, 16.27, 11.35, 10.31),
  #                        CS_BRKGA = c(10.78, 12.34, 14.84, 16.08, 24.66, 19.16, 21.49, 28.11, 35.53, 21.14, 27.48, 25.66, 36.88, 54.70, 66.10))
  #   boxplot(data_c,
  #           ylab="Número de Trocas", xlab ="Método",
  #           main=toupper("Número de Trocas - Grupo d"))
  #   
  #   boxplot(time_c,
  #           ylab="Tempo (segundos)", xlab ="Método",
  #           main=toupper("Tempo Computacional - Grupo d"))
  #   
  
  #Tabela C3
  
  
  
  
  
  
  
  data_c3 <- data.frame(Proposto = c(106.40, 88.50, 70.50, 52.90),
                        CS_BRKGA = c(106.80, 88.70, 70.70, 53.10))
  
  # time_c3 <- data.frame(Proposto = c(2.10, 3.39, 2.61, 3.93, 4.56, 2.69, 4.75, 9.59, 4.75, 6.56, 12.96, 13.41, 16.27, 11.35, 10.31),
  #                      CS_BRKGA = c(10.78, 12.34, 14.84, 16.08, 24.66, 19.16, 21.49, 28.11, 35.53, 21.14, 27.48, 25.66, 36.88, 54.70, 66.10))
  boxplot(data_c3,
          ylab="Número de Trocas", xlab ="Método",
          main=toupper("Número de Trocas - Grupo C-3"))
  
  #   boxplot(time_c3,
  #           ylab="Tempo (segundos)", xlab ="Método",
  #           main=toupper("Tempo Computacional - Grupo d"))
  
  
  data_c4 <- data.frame(Proposto = c(198.70, 174.00, 146.50, 114.00),
                        CS_BRKGA = c(199.80, 175.30, 147.50, 114.50))
  
  # time_c4 <- data.frame(Proposto = c(2.10, 3.39, 2.61, 3.93, 4.56, 2.69, 4.75, 9.59, 4.75, 6.56, 12.96, 13.41, 16.27, 11.35, 10.31),
  #                      CS_BRKGA = c(10.78, 12.34, 14.84, 16.08, 24.66, 19.16, 21.49, 28.11, 35.53, 21.14, 27.48, 25.66, 36.88, 54.70, 66.10))
  boxplot(data_c4,
          ylab="Número de Trocas", xlab ="Método",
          main=toupper("Número de Trocas - Grupo C-4"))
  
  #   boxplot(time_c4,
  #           ylab="Tempo (segundos)", xlab ="Método",
  #           main=toupper("Tempo Computacional - Grupo d"))
  #   
  
  
  
  
}


makeAll <- function() {
  
  basePath = "Instancias/Resultados/";
  yanasse = c("GrupoA/", 
              "GrupoB/", 
              "GrupoC/", 
              "GrupoD/", 
              "GrupoE/"
  )
  
  crama = c("C-1/",
            "C-2/",
            "C-3/",
            "C-4/"
  )
  
  catanzaro = c("A1/",
                "A2/",
                "A3/",
                "A4/",
                "B1/",
                "B2/",
                "B3/",
                "B4/",
                "C1/",
                "C2/",
                "C3/",
                "C4/",
                "D1/",
                "D2/",
                "D3/",
                "D4/"
  )
  
  all = c(yanasse, crama, catanzaro)
  
  
  for(instance in all)
  {
    print(paste("making summary table ", instance))
    makeSummaryTable( paste(basePath, instance, sep="")  ) ;
  }
  
  for(instance in yanasse)
  {
    
    print(paste("making antonio stats ", instance))
    statisticsAntonioNumbering( paste(basePath, instance, sep=""));
  }
  
  for(instance in c(crama, catanzaro))
  {
    
    print(paste("making crama stats ", instance))
    statisticsCramaNumbering( paste(basePath, instance, sep="") );
  }
  
}




readAllSummaryOnly <- function(filename){
  #nomes = c(#'Ant', 'BPI', 'FI', 'KOPT', 'MSG', 'NN','FST', 'FSTI', 'FSTF','FST_OPT', 'ILS','ILS_OPT', 'ILS_LS_2OPT'#,'ILS_LS_PART_2OPT_1','ILS_LS_PART_2OPT_2','ILS_LS_PART_2OPT_3','ILS_LS_PART_2OPT_4'#, "ILS_LS_22Swap", "ILS_LS_PART_22Swap"
  #          );
  nomes = c('FST', 'FST');
  #for(i in 1 : 20 )
  #{
  # nomes = c(nomes, paste("ILS_LS_PART_2OPT_", i, sep=""))
  #}
  
  print(nomes)
  allS <- read.table(paste(filename, "Summary", paste("Solution", nomes[1],".txt", sep=""), sep ="/"))
  allS <- allS[,1:3]
  names <- c("Instancia", "N_FST", "T_FST")
  for(i in 2:length(nomes))
  {
    currentSummary <- read.table(paste(filename, "Summary", paste("Solution", nomes[i],".txt", sep=""), sep ="/"))
    allS <- cbind(allS, currentSummary[,2:3]);
    names <- c(names, paste("N_",nomes[i], sep = ""), paste("T_",nomes[i], sep = ""))
  }
  colnames(allS) <- names
  allS
}

readAllTimeOnly <- function(filename){
  nomes = c('Ant', 'BPI', 'FI', 'KOPT', 'MSG', 'NN','FST', 'FSTI', 'FSTF','FST_OPT', 'ILS','ILS_OPT', 'ILS_LS_2OPT','ILS_LS_PART_2OPT'#, "ILS_LS_22Swap", "ILS_LS_PART_22Swap"
  );
  allS <- read.table(paste(filename, "Summary", paste("Solution", nomes[1],".txt", sep=""), sep ="/"))
  names <- c("Instancia", "N_Ant", "T_Ant")
  for(i in 2:length(nomes))
  {
    currentSummary <- read.table(paste(filename, "Summary", paste("Solution", nomes[i],".txt", sep=""), sep ="/"))
    allS <- cbind(allS, currentSummary[,2:3]);
    names <- c(names, paste("N_",nomes[i], sep = ""), paste("T_",nomes[i], sep = ""))
  }
  colnames(allS) <- names
  allS
}

allStats <- function(filepath, testNumber)
{
  
  instances = c('C-1', 'C-2', 'C-3', 'C-4', 'GrupoA', 'GrupoB', 'GrupoC', 'GrupoD', 'GrupoE');
  
  for(i in 1:length(instances))
  {
    print(instances[i])
    print(testNumber)
    makeSummaryTableNumbering( paste(filepath, instances[i], '/', sep='/') ,  testNumber)
  }
  
}


makeSummaryTableNumbering <- function(filename, testNumber)
{
  all <- readAllSummaryOnly(filename)
  bestResults <- findBestResults(filename, all)
  
  melhorResultado <- data.frame(all, bestResults)
  colnames(melhorResultado) <- c(colnames(all), "Melhores Resultado")
  
  write.table(format(melhorResultado, scientific=FALSE) , file = paste(filename,  "Resultados/AllSumary.txt", sep = ""), sep ="\t")
  write.csv(format(melhorResultado, scientific=FALSE) , file = paste(filename,  paste("Resultados/AllSumary", testNumber,".csv", sep=""), sep = "/"))
}

makeSummaryTable <- function(filename)
{
  all <- readAllSummaryOnly(filename)
  bestResults <- findBestResults(filename, all)
  
  melhorResultado <- data.frame(all, bestResults)
  colnames(melhorResultado) <- c(colnames(all), "Melhores Resultado")
  
  write.table(format(melhorResultado, scientific=FALSE) , file = paste(filename,  "Resultados/AllSumary.txt", sep = ""), sep ="\t")
  write.csv(format(melhorResultado, scientific=FALSE) , file = paste(filename,  paste("Resultados/AllSumary",".csv", sep=""), sep = "/"))
}


findBestResults <- function(filename, all)
{
  bestResults <- numeric(nrow(all))
  indice = seq(from = 2 , to = ncol(all), by = 4)
  
  ordinalRank = numeric(length(indice))
  cardinalRank = numeric(length(indice))
  names(ordinalRank) <- colnames(all[,indice])
  names(cardinalRank) <- colnames(all[,indice])
  bestResults <- read.csv(paste(filename, "BestResults", "BestResultsWithCap.csv", sep = "/"))
  
  for(i in 1:nrow(all))
  {
    best <- 100000
    ind <- 0
    ordem = rank(all[i,indice], ties.method = "min") # Rankea a instancia i.
    ordinalRank <- ordinalRank + ordem; # Soma a posicao de cada um na soma total.
    gapDistance <- all[i,indice] - bestResults[i,'trocas']
    cardinalRank <- cardinalRank + as.numeric(gapDistance)
  }
  ordinalRank <- ordinalRank/nrow(all); # pega a media das posicoes.
  cardinalRank <- cardinalRank/nrow(all); # pega a media das posicoes.
  
  
  ranks <- makeRanks(filename, ordinalRank, cardinalRank)
  print(ranks)
  
  bestResults[1:nrow(all),'trocas']
}

makeRanks <- function(filename, ordinalRank, cardinalRank)
{
  ordinalRankOrder <- rank(ordinalRank, ties.method = "min") # Descobre o ranking.
  ordinalRank <- ordinalRank[order(ordinalRankOrder)] # Ordena de acordo com o ranking. 
  ordinalRank <- data.frame(ordinalRank)
  
  cardinalRankOrder <- rank(cardinalRank, ties.method = "min") # Descobre o ranking.
  cardinalRank <- cardinalRank[order(cardinalRankOrder)] # Ordena de acordo com o ranking. 
  cardinalRank <- data.frame(cardinalRank)
  
  ranks <- data.frame(ordinalRank, cardinalRank)
  
  
  write.table(ranks, file = paste(filename,  "Resultados", "Ranks.txt", sep = "/"), sep ="\t")
  write.csv(ranks, file = paste(filename,  "Resultados", "Ranks.csv", sep = "/"))
  ranks
}

rankingOrdinal <- function(filename, ordinalRank)
{
  ranking <- rank(ordinalRank, ties.method = "min") # Descobre o ranking.
  ordinalRank <- ordinalRank[order(ranking)] # Ordena de acordo com o ranking. 
  ordinalRank <- data.frame(ordinalRank)
  
  
  write.table(ordinalRank, file = paste(filename,  "Resultados", "RankingOrdinal.txt", sep = "/"), sep ="\t")
  write.csv(ordinalRank, file = paste(filename,  "Resultados", "RankingOrdinal.csv", sep = "/"), sep=";")
  ordinalRank
}

rankingCardinal <- function(filename, cardinalRank)
{
  ranking <- rank(cardinalRank, ties.method = "min") # Descobre o ranking.
  cardinalRank <- cardinalRank[order(ranking)] # Ordena de acordo com o ranking. 
  cardinalRank <- data.frame(cardinalRank)
  
  write.table(cardinalRank, file = paste(filename,  "Resultados", "RankingCardinal.txt", sep = "/"), sep ="\t")
  write.csv(cardinalRank, file = paste(filename,  "Resultados", "RankingCardinal.csv", sep = "/"), sep=";")
  cardinalRank
}




testResults <- function(filepath)
{  
  numberOfRuns <- 2
  compare <- read.csv(paste(filepath, 'Resultados/Compare.csv', sep="/"), sep=";")
  
  proposed <- data.frame(compare)
  for(i in 1:2)
  {
    stats <- read.csv(file = paste(filepath,  "Resultados", paste("Stats", i, ".csv", sep=""), sep = "/"), sep =";", dec=",")
    proposed <- cbind(proposed, stats$N_ILS_LS_PART_2OPT)
  }
  
  meanResults <- data.frame( matrix( nrow = nrow(proposed), ncol = 3 ) )
  
  colnames(proposed) <- c(colnames(compare), 'Run #1', 'Run #2', 'Run #3', 'Run #4','Run #2')
  for(i in 1:nrow(proposed))
  {
    currentInstance <- as.double(as.vector(proposed[i,2:6]))
    meanResults[i, 1] <- mean(currentInstance)
    if( sum(!duplicated(currentInstance) == T) > 1)
    {
      shapiroResult <-shapiro.test(currentInstance)
      #print(shapiroResult)
      print(shapiroResult$statistic)
      meanResults[i, 2] <- shapiroResult$statistic
      meanResults[i, 3] <- shapiroResult$p.value
    }
  }
  colnames(meanResults) <- c('Mean', 'W', 'p-value')
  proposed <- cbind(proposed, meanResults)
  print(proposed)
  for(i in 2:6)
  {
    print(c(proposed[1:4,i]))
    print( as.numeric(as.character(proposed[,1])[1:4]) )
    wilcoxResult <- wilcox.test(as.numeric(as.character(proposed[,1])[1:4]), as.numeric(proposed[1:4,i]), paired=TRUE)
    print(wilcoxResult)
  }
  write.table(proposed, file = paste(filepath,  "Resultados", "Testes.csv", sep = "/"), dec= ",", sep=";", row.names = F)
}







#CALCULA A MEDIA E O VALOR MINIMO OBTIDO EM RELAÇÃO A SOLUÇÃO E TEMPO! (GrupoA - GrupoE)

statisticsAntonioNumbering <- function(filepath)
{
  allSummary <- read.csv(paste(filepath, paste('Resultados/AllSumary', '.csv', sep=""), sep="/"))
  instanceDetails <- read.csv(paste(filepath, 'Resultados/InstanceDetails.csv', sep="/"))
  compareWith <- read.csv(paste(filepath, 'Resultados/Compare.csv', sep="/"), sep=';')
  
  indice <- seq(from = 3 , to = ncol(allSummary) - 2, by = 2) # get the columns with the number of switches.
  indiceTimes <- seq(from = 4 , to = ncol(allSummary) - 1, by = 2) # get the columns with the number of switches.
  #indiceBestTimes <- seq(from = 2 , to = ncol(allSummary) - 1, by = 2) # get the columns with the number of switches.
  #indiceIter <- seq(from = 6 , to = ncol(allSummary) - 1, by = 2) # get the columns with the number of switches.
  switchesSummary <- data.frame(  allSummary[,indice] )
  timesSummary <- data.frame(  allSummary[,indiceTimes] )
  #bestTimesSummary <- data.frame(  allSummary[,indiceBestTimes] )
  #iterSummary <- data.frame(  allSummary[,indiceIter] )
  uniqueDet <- instanceDetails[!duplicated(instanceDetails), ]
  uniqueDet <- uniqueDet[order(uniqueDet$Cap),]
  uniqueDet <- uniqueDet[order(uniqueDet$M),]
  uniqueDet <- uniqueDet[order(uniqueDet$N),]
  
  
  comp <- data.frame( matrix( nrow = nrow(instanceDetails), ncol = ncol(switchesSummary) ) ) 
  colnames(comp) <- colnames( allSummary[indice] )
  
  compTime <- data.frame( matrix( nrow = nrow(instanceDetails), ncol = ncol(timesSummary) ) ) 
  colnames(compTime) <- colnames( allSummary[indiceTimes] )
  
  #compBestTime <- data.frame( matrix( nrow = nrow(instanceDetails), ncol = ncol(timesSummary) ) ) 
  #colnames(compBestTime) <- colnames( allSummary[indiceTimes] )
  
  #iterTime <- data.frame( matrix( nrow = nrow(instanceDetails), ncol = ncol(timesSummary) ) ) 
  #colnames(iterTime) <- colnames( allSummary[indiceTimes] )
  
  for (i in 0:(nrow(instanceDetails) - 1) )
  { 
    for (j in 1:ncol(switchesSummary)  )
    {
      comp[i+1, j] <- sum( switchesSummary[  ((i*10) + 1 ): ((i*10) + 10), j] ) / 10
      compTime[i+1, j] <- sum( timesSummary[  ((i*10) + 1 ): ((i*10) + 10), j] ) / 10
   #   compBestTime[i+1, j] <- sum( bestTimesSummary[  ((i*10) + 1 ): ((i*10) + 10), j] ) / 10
  #    iterTime[i+1, j] <- sum( iterSummary[  ((i*10) + 1 ): ((i*10) + 10), j] ) / 10
    }
  }
  
  
  finalComp <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(switchesSummary) ) ) 
  colnames(finalComp) <- colnames( comp )
  finalCompTime <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(timesSummary) ) ) 
  colnames(finalCompTime) <- colnames( comp )
  #finalCompBestTime <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(bestTimesSummary) ) ) 
  #colnames(finalCompBestTime) <- colnames( comp )
  #finalCompIter <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(iterSummary) ) ) 
  #colnames(finalCompIter) <- colnames( comp )
  
  for (i in 1:nrow(uniqueDet)) 
  {
    inst = uniqueDet[i,];
    currentInstance <- instanceDetails$N == inst$N & instanceDetails$M == inst$M & instanceDetails$Cap == inst$Cap
    for (j in 1:ncol(switchesSummary))
    {
      #Wprint(sum( comp [ currentInstance , j] ))
      finalComp[i,j] <- sum( comp [ currentInstance , j] )/sum(currentInstance)
      finalCompTime[i,j] <- sum( compTime [ currentInstance , j] )/sum(currentInstance)
   #   finalCompBestTime[i,j] <- sum( compBestTime [ currentInstance , j] )/sum(currentInstance)
  #    finalCompIter[i,j] <- sum( iterTime [ currentInstance , j] )/sum(currentInstance)
    }
  }
  finalComp <- round( finalComp[,], 2)
  finalCompTime <- round( finalCompTime[,], 2)
  
  #finalCompBestTime <- round( finalCompBestTime[,], 2)
  #finalCompIter <- round( finalCompIter[,], 2)
  
  
  finalComp <- cbind( finalComp, apply(finalComp[,], 1, min), apply(finalComp[,], 1, mean),  apply(finalComp[,], 1, sd))
  colnames(finalComp)[c(ncol(finalComp)-2,ncol(finalComp)-1, ncol(finalComp))] <- c("min", "mean","sd")
  
  finalCompTime <- cbind( finalCompTime, apply(finalCompTime[,], 1, min), apply(finalCompTime[,], 1, mean) , apply(finalCompTime[,], 1, sd)  )
  colnames(finalCompTime)[c(ncol(finalCompTime)-2, ncol(finalCompTime)-1, ncol(finalCompTime))] <- c("min", "mean","sd")
  
  #finalCompBestTime <- cbind( finalCompBestTime, apply(finalCompBestTime[,], 1, min), apply(finalCompBestTime[,], 1, mean) , apply(finalCompBestTime[,], 1, sd)  )
  #colnames(finalCompBestTime)[c(ncol(finalCompBestTime)-2, ncol(finalCompBestTime)-1, ncol(finalCompBestTime))] <- c("min", "mean","sd")
  
  #finalCompIter <- cbind( finalCompIter, apply(finalCompIter[,], 1, min), apply(finalCompIter[,], 1, mean) , apply(finalCompIter[,], 1, sd)  )
  #colnames(finalCompIter)[c(ncol(finalCompIter)-2, ncol(finalCompIter)-1, ncol(finalCompIter))] <- c("min", "mean","sd")
  
  
  print(finalComp)
  print(finalCompTime)
  
  write.table( finalComp[ ,1:ncol(finalComp) ], file = paste(filepath,  "Resultados", paste("Stats", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
  write.table( finalCompTime[ ,1:ncol(finalCompTime) ], file = paste(filepath,  "Resultados", paste("StatsTime", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
  #write.table( finalCompBestTime[ ,1:ncol(finalCompBestTime) ], file = paste(filepath,  "Resultados", paste("StatsBestTime", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
  #write.table( finalCompIter[ ,1:ncol(finalCompIter) ], file = paste(filepath,  "Resultados", paste("StatsIter ", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
}






#CALCULA A MEDIA E O VALOR MINIMO OBTIDO EM RELAÇÃO A SOLUÇÃO E TEMPO! (C1 - C4)

statisticsCramaNumbering <- function(filepath)
{
  allSummary <- read.csv(paste(filepath, paste('Resultados/AllSumary', '.csv', sep=""), sep="/"))
  instanceDetails <- read.csv(paste(filepath, 'Resultados/InstanceDetails.csv', sep="/"))
  compareWith <- read.csv(paste(filepath, 'Resultados/Compare.csv', sep="/"), sep=';')
  
  
  indice <- seq(from = 3 , to = ncol(allSummary) - 2, by = 2) # get the columns with the number of switches.
  indiceTimes <- seq(from = 4 , to = ncol(allSummary) - 1, by = 2) # get the columns with the number of switches.
  #indiceBestTimes <- seq(from = 2 , to = ncol(allSummary) - 1, by = 2) # get the columns with the number of switches.
  #indiceIter <- seq(from = 6 , to = ncol(allSummary) - 1, by = 2) # get the columns with the number of switches.
  switchesSummary <- data.frame(  allSummary[,indice] )
  timesSummary <- data.frame(  allSummary[,indiceTimes] )
  #bestTimesSummary <- data.frame(  allSummary[,indiceBestTimes] )
  #iterSummary <- data.frame(  allSummary[,indiceIter] )
  uniqueDet <- instanceDetails[!duplicated(instanceDetails), ]
  uniqueDet <- uniqueDet[order(uniqueDet$Cap),]
  uniqueDet <- uniqueDet[order(uniqueDet$M),]
  uniqueDet <- uniqueDet[order(uniqueDet$N),]
  
  
  comp <- switchesSummary
  compTime <- timesSummary
  #compBestTime <- bestTimesSummary
  #iterTime <- iterSummary
  
  finalComp <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(switchesSummary) ) ) 
  colnames(finalComp) <- colnames( comp )
  finalCompTime <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(timesSummary) ) ) 
  colnames(finalCompTime) <- colnames( comp )
  
  #finalCompBestTime <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(bestTimesSummary) ) ) 
  #colnames(finalCompBestTime) <- colnames( comp )
  #finalCompIter <- data.frame( matrix( nrow = nrow(uniqueDet), ncol = ncol(iterSummary) ) ) 
  #colnames(finalCompIter) <- colnames( comp )
  
  
  for (i in 1:nrow(uniqueDet)) 
  {
    inst = uniqueDet[i,];
    currentInstance <- instanceDetails$N == inst$N & instanceDetails$M == inst$M & instanceDetails$Cap == inst$Cap
    for (j in 1:ncol(switchesSummary))
    {
      #Wprint(sum( comp [ currentInstance , j] ))
      finalComp[i,j] <- sum( comp [ currentInstance , j] )/sum(currentInstance)
      print(sum( comp [ currentInstance , j] ));
      print(sum(currentInstance));
      finalCompTime[i,j] <- sum( compTime [ currentInstance , j] )/sum(currentInstance)
      #finalCompBestTime[i,j] <- sum( compBestTime [ currentInstance , j] )/sum(currentInstance)
      #finalCompIter[i,j] <- sum( iterTime [ currentInstance , j] )/sum(currentInstance)
    }
  }
  finalComp <- round( finalComp[,], 2)
  finalCompTime <- round( finalCompTime[,], 2)
  
  #finalCompBestTime <- round( finalCompBestTime[,], 2)
  #finalCompIter <- round( finalCompIter[,], 2)
  
  
  finalComp <- cbind( finalComp, apply(finalComp[,], 1, min), apply(finalComp[,], 1, mean),  apply(finalComp[,], 1, sd))
  colnames(finalComp)[c(ncol(finalComp)-2,ncol(finalComp)-1, ncol(finalComp))] <- c("min", "mean","sd")
  
  finalCompTime <- cbind( finalCompTime, apply(finalCompTime[,], 1, min), apply(finalCompTime[,], 1, mean) , apply(finalCompTime[,], 1, sd)  )
  colnames(finalCompTime)[c(ncol(finalCompTime)-2, ncol(finalCompTime)-1, ncol(finalCompTime))] <- c("min", "mean","sd")
  #finalCompBestTime <- cbind( finalCompBestTime, apply(finalCompBestTime[,], 1, min), apply(finalCompBestTime[,], 1, mean) , apply(finalCompBestTime[,], 1, sd)  )
  #colnames(finalCompBestTime)[c(ncol(finalCompBestTime)-2, ncol(finalCompBestTime)-1, ncol(finalCompBestTime))] <- c("min", "mean","sd")
  
  #finalCompIter <- cbind( finalCompIter, apply(finalCompIter[,], 1, min), apply(finalCompIter[,], 1, mean) , apply(finalCompIter[,], 1, sd)  )
  #colnames(finalCompIter)[c(ncol(finalCompIter)-2, ncol(finalCompIter)-1, ncol(finalCompIter))] <- c("min", "mean","sd")
  
  
  #finalComp <- cbind( rbind(uniqueDet, c(NA, NA, NA) ) , compareWith, finalComp  )
  #finalCompTime <- cbind( rbind(uniqueDet, c(NA, NA, NA) ) , compareWith, finalCompTime  )
  
  
  print(finalComp)
  print(finalCompTime)
  write.table( finalComp[ ,1:ncol(finalComp) ], file = paste(filepath,  "Resultados", paste("Stats", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
  write.table( finalCompTime[ ,1:ncol(finalCompTime) ], file = paste(filepath,  "Resultados", paste("StatsTime", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
  #write.table( finalCompBestTime[ ,1:ncol(finalCompBestTime) ], file = paste(filepath,  "Resultados", paste("StatsBestTime", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
  #write.table( finalCompIter[ ,1:ncol(finalCompIter) ], file = paste(filepath,  "Resultados", paste("StatsIter ", ".csv", sep=""), sep = "/"), dec= ".", sep=";", row.names = F)
  
}



allStatsAntonio <- function(filepath)
{
  
  for(i in 1:2)
  {
    statisticsAntonioNumbering(filepath, i)
  }
  
}
allStatsCrama <- function(filepath)
{
  
  for(i in 1:2)
  {
    statisticsCramaNumbering(filepath, i)
  }
  
}
