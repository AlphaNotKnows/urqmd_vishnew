      Program main
      IMPLICIT NONE
      DOUBLE PRECISION Pi
      PARAMETER (Pi = 3.14159)

      INTEGER iEvent, M, Total_Event, datasize, N_EbE
      PARAMETER (datasize = 100000)           ! MAX multiplicity in single event
      PARAMETER (N_EbE = 100000)              ! MAX event number
      INTEGER I, J, K
      character(10) dummy
      INTEGER :: pid(datasize)
      INTEGER :: Charge(datasize)
      Double precision :: Mass(datasize)
      Double precision :: PT(datasize)
      Double precision :: Pphi(datasize)
      Double precision :: Rapid(datasize)

      INTEGER N_pT, N_Pphi, N_Rapid           ! momentum space grid numbers
      INTEGER g_pT, g_Pphi, g_Rapid           ! INTEGER(particle momentum space)
      Double precision d_PT, d_Pphi, d_Rapid  ! 
      Double precision D_N, SUM
      PARAMETER (N_Rapid = 20)
      PARAMETER (d_Rapid = 0.5)
      INTEGER :: num(-N_Rapid:N_Rapid)
      Double precision :: dN_dy(-N_Rapid:N_Rapid)
      Double precision :: V1(-N_Rapid:N_Rapid)
      INTEGER :: V1_num(-N_Rapid:N_Rapid)      

      iEvent=0
      dN_dy = 0.0
      V1 = 0.0
      V1_num = 0
      OPEN(1, FILE='../results/particle.dat', STATUS='OLD'
     &   ,ACCESS="STREAM",
     &   FORM="UNFORMATTED")  
  992  CONTINUE          
        READ(1,END=1002) M
        iEvent=iEvent+1
        IF(M.GT.datasize) THEn
          write(*,*) 'ERROR:Multiplicity exceed! M=', M
          STOP
        END IF
C-------Initialize input database------------------
        pid = 0
        Charge = 0
        Mass  = 0.0
        PT = 0.0
        Pphi = 0.0
        Rapid = 0.0
C-------INPUT particle information in each event---
        DO I = 1, M
           READ(1) pid(I),Charge(I),Mass(I),PT(I),Pphi(I),Rapid(I)
        END DO
C-------Search particles with charge-----------
           num = 0.0
           DO I = 1,M
             IF(Charge(I).NE.0) THEN
                IF(Rapid(I).GE.0) THEN
                   g_Rapid = int((Rapid(I) + d_Rapid/2) / d_Rapid)
                ELSE IF(Rapid(I).LT.0) THEN
                   g_Rapid = int((Rapid(I) - d_Rapid/2) / d_Rapid)
                END IF                 
                IF(g_Rapid.GT.N_Rapid) THEN
                   g_Rapid = N_Rapid
                ELSE IF(g_Rapid.LT.-N_Rapid) THEn
                   g_Rapid = -N_Rapid
                END IF
                Num(g_Rapid) = Num(g_Rapid) + 1
C---------- define v1 in rapidity direction---------
                IF(pid(I).EQ.211) THEN
                  V1(g_Rapid) = V1(g_Rapid) + cos(Pphi(i))
                  V1_num(g_Rapid) = V1_num(g_Rapid) + 1
                END IF  
C---------- v1 defination end ----------------------                
             END IF 
           END DO 

C----------Calculate dN_dy------------------

      
              DO K = -N_Rapid, N_Rapid

              dN_dy(K) = dN_dy(K) + Num(k) / d_Rapid

              END DO


           GOTO 992
 1002    CONTINUE 
      Close(1)


C----------------------FINISH EBE CALCULATION---------------------------------
           Total_Event = iEvent
           write(*,*) 'Total_Event = ', Total_Event
           dN_dy = dN_dy / Total_Event
C           write(*,*) 'SUM = ', SUM
           OPEN(11, FILE='../results/dNchdy.dat',STATUS='REPLACE')
           DO K = -N_Rapid, N_Rapid
              write(11,*) K*d_Rapid,  dN_dy(K)  
           END DO
           Close(11)
           write(*,*) 'dNdy_ch calculation finished!'

           OPEN(11, FILE='../results/v1-rapidity.dat',STATUS='REPLACE')
           DO K = -N_Rapid, N_Rapid
              write(11,*) K*d_Rapid,  V1(K) / V1_num(K)  
           END DO
           Close(11)           
           write(*,*) 'V1-rapidity calculation finished!'
      END
