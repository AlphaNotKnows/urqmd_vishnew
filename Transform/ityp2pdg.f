
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      function pdgid (ityp, iso3)
c
c     Revision : 1.0
c
coutput pdgid  : Particle-ID according to Particle Data Group  
c 
c     converts UrQMD-Id to PDG-Id 
c
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

      implicit none

c $Id: comres.f,v 1.15 2003/06/29 14:26:36 weber Exp $
c
cdes This file contains definitions for the collision term
c
      integer maxbar,maxbra,minbar
      integer offmeson,maxmeson,pimeson,maxbrm,minnuc,mindel
      integer maxbrs1,maxbrs2
      integer numnuc,numdel,nucleon,maxnuc,maxdel
      integer minmes,maxmes


      parameter (minnuc=1) ! lowest baryon particle ID 
      parameter (minmes=100) ! lowest meson particle ID
corig      parameter (maxmes=132) ! hightest meson particle ID
c add 5 charmed mesons to array
      parameter (maxmes=139) ! hightest meson particle ID

c number of resonances of a kind
      parameter (numnuc=16) ! number of nucleon resonances
      parameter (numdel=10) ! number of delta resonances
c indices of minimal and maximal itype of a kind (redundant but nice)
      parameter (maxnuc=minnuc+numnuc-1) ! highest nucleon ID
      parameter (mindel=minnuc+maxnuc)   ! lowest delta ID
      parameter (maxdel=mindel+numdel-1) ! highest delta ID

c minres & maxres define the range of nonstable & nonstrange baryons
      integer minres,maxres
      parameter (minres=minnuc+1) ! lowest baryon resonance ID
      parameter (maxres=maxdel)   ! highest (nonstrange) baryon 
                                  ! resonance ID

c strangenes.ne.0 baryon resonances
      integer minlam,minsig,mincas,minome
      integer numlam,numsig,numcas,numome
      integer maxlam,maxsig,maxcas,maxome
      parameter (numlam=13) ! number of lambda states
      parameter (numsig=9)  ! number of sigma states
      parameter (numcas=6)  ! number of cascade states
      parameter (numome=1)  ! number of omega states
      parameter (minlam=mindel+numdel)   ! ID of lowest lambda state
      parameter (maxlam=minlam+numlam-1) ! ID of highest lambda state
      parameter (minsig=minlam+numlam)   ! ID of lowest sigma state
      parameter (maxsig=minsig+numsig-1) ! ID of highest sigma state
      parameter (mincas=minsig+numsig)   ! ID of lowest cascade state
      parameter (maxcas=mincas+numcas-1) ! ID of highest cascade state
      parameter (minome=mincas+numcas)   ! ID of lowest omega state
      parameter (maxome=minome+numome-1) ! ID of highest omega state

c minbar & maxbar define the range of all baryons
      parameter (minbar=minnuc) ! ID of lowest baryon state
      parameter (maxbar=maxome) ! ID of highest baryon state

      parameter (offmeson=minmes) ! offset between zero and lowest 
                                  ! meson state
      parameter (maxmeson=maxmes) ! ID of highest meson state
c... these variables are in principal obsolete and should be exchanged 
c were referenced 

c... avoid hard coded itypes
      integer itrho,itome,iteta,itkaon,itphi,itetapr
      parameter (itkaon=106)   ! ID of kaon
      parameter (itrho=104)    ! ID of rho meson 
      parameter (itome=103)    ! ID of omega meson
      parameter (iteta=102)    ! ID of eta
      parameter (itphi=109)    ! ID of phi
      parameter (itetapr=107)  ! ID of eta'
      parameter (pimeson=101)  ! ID of $\pi$
      parameter (nucleon=minnuc) ! ID of nucleon

      integer itmin,itmax
      parameter (itmin=minnuc)  ! lowest defined ID
      parameter (itmax=maxmes)  ! highest defined ID
c
      parameter (maxbra=11)  ! decay channels for $s=0$ baryon resonances
corig      parameter (maxbrm=25) ! decay channels for meson resonances
c add 2 decay channels for D*
      parameter (maxbrm=27) ! decay channels for meson resonances
      parameter (maxbrs1=10)! decay channels for $s=1$ baryon resonances
      parameter (maxbrs2=3) ! decay channels for $s=2$ baryon resonances

c 
       integer mlt2it(maxmes-minmes) ! meson IDs sorted by multipletts


      real*8 massoff,mresmin,mresmax
      parameter (massoff=1d-4)      ! offset for mass generation
      parameter (mresmin=1.0765d0)  ! minimum baryon resonance mass
      parameter (mresmax=3.5d0)       ! maximum baryon resonance mass

      character*45 versiontag
      common /versioning/ versiontag

      real*8 massres(minbar:maxbar),widres(minbar:maxbar)
      real*8 branmes(0:maxbrm,minmes+1:maxmes)
      real*8 branres(0:maxbra,minnuc+1:maxdel)
      real*8 branbs1(0:maxbrs1,minlam+1:maxsig)
      real*8 branbs2(0:maxbrs2,mincas+1:maxcas)
      integer Jres(minbar:maxbar)
      integer Jmes(minmes:maxmes)
      integer pares(minbar:maxbar),pames(minmes:maxmes)
      integer Isores(minbar:maxbar), Isomes(minmes:maxmes)
      integer brtype(4,0:maxbra),bmtype(4,0:maxbrm)
      integer bs1type(4,0:maxbrs1),bs2type(4,0:maxbrs2)
      real*8 massmes(minmes:maxmes)
      real*8 mmesmn(minmes:maxmes)
      real*8 widmes(minmes:maxmes)
      integer strres(minbar:maxbar),strmes(minmes:maxmes)
      integer chrmres(minbar:maxbar),chrmmes(minmes:maxmes)

      integer lbr(0:maxbra,minnuc+1:maxdel)
      integer lbs1(0:maxbrs1,minlam+1:maxsig)
      integer lbs2(0:maxbrs2,mincas+1:maxcas)
      integer lbm(0:maxbrm,minmes+1:maxmes)

      common /resonances/ massres,widres,massmes,widmes,mmesmn,
     ,                    branres,branmes,branbs1,branbs2,
     ,                    bs1type,bs2type,lbs1,lbs2,lbm,
     ,                    jres,jmes,lbr,brtype,pares,pames,
     ,                    bmtype,
     ,                    Isores,Isomes,strres,strmes,mlt2it,
     ,                    chrmres,chrmmes

c     massres   : baryon mass table
c     widres    : baryon decay width table
c     massmes   : meson mass table
c     widmes    : meson decay width table
c     mmesmn    : table of minimum masses for meson resonances
c     branres   : branching ratios for $s=0$ baryon resonances
c     branmes   : branching ratios for meson resonances
c     branbs1   : branching ratios for $s=1$ baryon resonances
c     branbs2   : branching ratios for $s=2$ baryon resonances
c     brtype    : definitions of the decay branches for $s=0$ baryon resonances
c     bmtype    : definitions of the decay branches for meson resonances
c     bs1type   : definitions of the decay branches for $s=1$ baryon resonances
c     bs2type   : definitions of the decay branches for $s=2$ baryon resonances
c     lbr       : decay angular momenta for $s=0$ baryon decays
c     lbm       : decay angular momenta for meson decays
c     lbs1      : decay angular momenta for $s=1$ baryon decays
c     lbs2      : decay angular momenta for $s=2$ baryon decays
c     jres      : spin table for baryons
c     jmes      : spin table for mesons
c     pares     : parity table for baryons
c     pames     : parity table for mesons
c     isores    : isospin table for baryons
c     isomes    : isospin table for mesons
c     strres    : strangeness table for baryons
c     strmes    : strangeness table for mesons 
c     
c
ccccccccccccccccccccc sigtab-declarations cccccccccccccccccccccccccccccccccc

      integer itblsz,nsigs,maxreac,maxpsig,sigver
c     VERSION NUMBER of SIGTAB
      parameter (sigver = 1000) ! version number for collision 
                                ! term and tables
ccccccccccccccccccccccccccccccccccccccc
c

      parameter (maxreac = 15) ! maximum number of collision classes
      parameter (maxpsig = 21) ! maximum number of cross 
                               ! sections per class
      parameter (nsigs = 10)   ! number of tabulated cross sections

      PARAMETER (ITBLSZ= 100)  ! table size of cross section tables


c
      integer sigmaLN(maxpsig,2,maxreac)
      integer sigmainf(nsigs,20)
      real*8 sigmascal(nsigs,5), sigmas(nsigs,itblsz)
c
      common/sigtabi/sigmaln,sigmainf
      common/sigtabr/sigmas,sigmascal

c     sigmaln   : pointer array connecting collision classes with cross sections
c     sigmainf  : information related to tabulated cross sections
c     sigmascal : information related to tabulated cross sections
c     sigmas    : tabulated cross sections

      integer pdgid
      integer ityp
      integer iso3

      integer tab_size
      parameter (TAB_SIZE = 174)

      logical anti
      integer abs_ityp
      integer norm_iso3
      integer idtab(3,TAB_SIZE)
      integer first
      integer last
      integer next
      integer isoit

      data idtab/
c Neutron
     .       1, -1,  2112,  
c Proton
     .       1,  1,  2212,
c N*
     .       2, -1, 12112,        2,  1, 12212,
     .       3, -1,  1214,        3,  1,  2124, 
     .       4, -1, 22112,        4,  1, 22212,
     .       5, -1, 32112,        5,  1, 32212,
     .       6, -1,  2116,        6,  1,  2216,
     .       7, -1, 12116,        7,  1, 12216,
     .       8, -1, 21214,        8,  1, 22124,
     .       9, -1, 42112,        9,  1, 42212, 
     .      10, -1, 31214,       10,  1, 32124, 
     .      14, -1,  1218,       14,  1,  2128, 
c Delta
     .      17, -3,  1114,  17, -1,  2114,  17, 1,  2214,  17, 3,  2224,
     .      18, -3, 31114,  18, -1, 32114,  18, 1, 32214,  18, 3, 32224,
     .      19, -3,  1112,  19, -1,  1212,  19, 1,  2122,  19, 3,  2222,
     .      20, -3, 11114,  20, -1, 12114,  20, 1, 12214,  20, 3, 12224,
     .      21, -3, 11112,  21, -1, 11212,  21, 1, 12122,  21, 3, 12222,
     .      22, -3,  1116,  22, -1,  1216,  22, 1,  2126,  22, 3,  2226,
     .      23, -3, 21112,  23, -1, 21212,  23, 1, 22122,  23, 3, 22222,
     .      24, -3, 21114,  24, -1, 22114,  24, 1, 22214,  24, 3, 22224,
     .      25, -3, 11116,  25, -1, 11216,  25, 1, 12126,  25, 3, 12226,
     .      26, -3,  1118,  26, -1,  2118,  26, 1,  2218,  26, 3,  2228,
c Lambda
     .      27,  0,  3122,
     .      28,  0, 13122,   
     .      29,  0,  3124,   
     .      30,  0, 23122,   
     .      31,  0, 33122,
     .      32,  0, 13124,
     .      33,  0, 43122,   
     .      34,  0, 53122,   
     .      35,  0,  3126,   
     .      36,  0, 13126,   
     .      37,  0, 23124,   
     .      38,  0,  3128,   
     .      39,  0, 23126,   
c Sigma
     .      40, -2,  3112,    40,  0,  3212,    40,  2,  3222,
     .      41, -2,  3114,    41,  0,  3214,    41,  2,  3224,
     .      42, -2, 13112,    42,  0, 13212,    42,  2, 13222,
     .      43, -2, 13114,    43,  0, 13214,    43,  2, 13224,
     .      44, -2, 23112,    44,  0, 23212,    44,  2, 23222,
     .      45, -2,  3116,    45,  0,  3216,    45,  2,  3226,
     .      46, -2, 13116,    46,  0, 13216,    46,  2, 13226,
     .      47, -2, 23114,    47,  0, 23214,    47,  2, 23224,
     .      48, -2,  3118,    48,  0,  3218,    48,  2,  3228,
c Xi
     .      49, -1,  3312,     49,  1,  3322,
     .      50, -1,  3314,     50,  1,  3324,
     .      52, -1, 13314,     52,  1, 13324,
c Omega
     .      55,  0,  3334,
c gamma
     .     100,  0,    22, 
c pion
     .     101, -2,  -211,    101,  0,   111,    101,  2,   211,
c eta
     .     102,  0,   221,
c omega
     .     103,  0,   223,
c rho
     .     104, -2,  -213,    104,  0,   113,    104,  2,   213,
c f0(980)
     .     105,  0, 10221,
c kaon
     .     106, -1,   311,    106,  1,   321,
c eta'
     .     107,  0,   331,
c k*(892)
     .     108, -1,   313,    108,  1,   323,
c phi
     .     109,  0,   333,
c k0*(1430)
     .     110, -1, 10313,    110,  1, 10323,
c a0(980)
     .     111, -2,-10211,    111,  0, 10111,    111,  2, 10211,
c f0(1370)
     .     112,  0, 20221,
c k1(1270)
     .     113, -1, 10313,    113,  1, 10323,
c a1(1260)
     .     114, -2,-20213,    114,  0, 20113,    114,  2, 20213,
c f1(1285)
     .     115,  0, 20223,
c f1'(1510)
     .     116,  0, 40223,
c k2*(1430)
     .     117, -1,   315,    117,  1,   325,
c a2(1329)
     .     118, -2,  -215,    118,  0,   115,    118,  2,   215,
c f2(1270)
     .     119,  0,   225,
c f2'(1525)
     .     120,  0,   335,
c k1(1400)
     .     121, -1, 20313,    121,  1, 20323,
c b1
     .     122, -2,-10213,    122,  0, 10113,    122,  2, 10213,
c h1
     .     123,  0, 10223,
c K* (1410)
     .     125, -1, 30313,    125,  1, 30323,
c rho (1450)
     .     126, -2,-40213,    126,  0, 40113,    126,  2, 40213,
c omega (1420)
     .     127,  0, 50223,
c phi(1680)
     .     128,  0, 10333,
c k*(1680)
     .     129, -1, 40313,    129,  1, 40323,
c rho(1700)
     .     130, -2,-30213,    130,  0, 30113,    130,  2, 30213,
c omega(1600)
     .     131,  0, 60223,
c phi(1850)     
     .     132,  0,   337,
c D
     .     133,  -1,   421,    133,   1,   411,  
c D*
     .     134,  -1, 10421,    134,   1, 10411,  
c J/Psi
     .     135,  0, 443,
c Chi_c
     .     136,  0, 100443,
c Psi'
     .     137,  0, 10441,
c Ds
     .     138,   0,   431,  
c Ds*
     .     139,   0,   433 /


c PYTHIA pdgid's (only need to subtract the offset!)
      if(abs(ityp).gt.1000) then
         if(ityp.gt.0) then
            pdgid=ityp-1000
         else
            pdgid=-1*(abs(ityp)-1000)
         endif
         return
      endif

cb check for antiparticles
      if (ityp.lt.0) then
cl its an antiparticle         
         anti = .true.
         abs_ityp = abs(ityp)
         norm_iso3 = -iso3
cl only mesons with odd isospin can have a negative ITYPE
         if ((abs_ityp.gt.minmes).and.
     .        (mod(isoit(abs_ityp),2).eq.0)) then
            call error ('pdgid','Negative ITYP not allowed',
     .           dble(ityp),3)
            pdgid = 0
            return
         endif
      else
         anti = .false.
         abs_ityp = ityp
         norm_iso3 = iso3
      endif

cb search for the ITYP in IDTAB

      first = 1
      last = TAB_SIZE
      if (idtab(1,first).eq.abs_ityp) then 
         next = first 
         goto 200
      endif
      if (idtab(1,last).eq.abs_ityp) then
         next = last 
         goto 200
      endif

 100  continue

cl ITYP not found in IDTAB
      if (last.le.(first+1)) then
         pdgid = 0
         return
      endif

      next = (first+last)/2

      if (idtab(1,next).lt.abs_ityp) then 
         first = next
         goto 100
      elseif (idtab(1,next).gt.abs_ityp) then
         last = next
         goto 100
      endif

 200  continue

cl calculate the entry with the wanted ISO3
      next = next - (idtab(2,next)-norm_iso3)/2
      
cl check if we found the correct values in IDTAB
      if ((idtab(1,next).eq.abs_ityp).and.
     .    (idtab(2,next).eq.norm_iso3)) then
         if (anti) then
            pdgid = -idtab(3,next)
         else
            pdgid = idtab(3,next)
         endif
      else
         call error ('pdgid','Error in tablelookup',dble(next),3)
         pdgid = 0
      endif
      
      return
      end

cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
      subroutine error (function_name, message, value, level)
c
c     Revision : 1.0
c
c     output of errors and warnings
c
cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc

      implicit none

      character function_name*(*)
      character message*(*)
      real*8 value
      integer level

c $Id: inputs.f,v 1.4 2000/01/12 16:02:36 bass Exp $
c     include file for data from the input subroutine
      integer nevents,spityp(2),prspflg
      integer trspflg,spiso3(2),outsteps,bflag,srtflag,efuncflag
      integer nsrt,npb,firstev
      real*8  srtmin,srtmax,pbeam,betann,betatar,betapro
      real*8  pbmin,pbmax

      common /inputs/nevents,spityp,prspflg,trspflg,
     &               spiso3,outsteps,bflag,srtflag,efuncflag,nsrt,
     &               firstev, npb
      common /input2/ srtmin,srtmax,pbeam,betann,betatar,betapro,
     &                pbmin, pbmax

c maximum number of test particle per nucleon
      integer MaxNTest
      parameter (MaxNTest=20)
c
c maximum mass for projectile and target
      integer AAmax
      parameter(AAmax=300)
c storage arrays for projectile and target nuclei
      integer PT_iso3(AAmax*MaxNTest,2),PT_ityp(AAmax*MaxNTest,2)
      integer PT_spin(AAmax*MaxNTest,2),PT_charge(AAmax*MaxNTest,2)
      integer PT_AA(2),PT_uid(AAmax*MaxNTest,2)
      real*8 PT_r0(AAmax*MaxNTest,2),PT_rx(AAmax*MaxNTest,2)
      real*8 PT_ry(AAmax*MaxNTest,2),PT_rz(AAmax*MaxNTest,2)
      real*8 PT_p0(AAmax*MaxNTest,2),PT_px(AAmax*MaxNTest,2)
      real*8 PT_py(AAmax*MaxNTest,2),PT_pz(AAmax*MaxNTest,2)
      real*8 PT_dectime(AAmax*MaxNTest,2),PT_fmass(AAmax*MaxNTest,2)
      real*8 PT_rho(AAmax*MaxNTest,2),PT_pmax(AAmax*MaxNTest,2)

c common blocks (data transfer between cascinit and getinit)
      common/ProTarInts/PT_iso3,PT_ityp,PT_spin,PT_charge,PT_AA,PT_uid
      common/ProTarReals/PT_r0,PT_rx,PT_ry,PT_rz,PT_fmass,PT_dectime,
     &                   PT_p0,PT_px,PT_py,PT_pz,PT_rho,PT_pmax

      integer errdev

      errdev=6

      if ((level.lt.1).or.(level.gt.3)) then
         write (errdev,*) '*** Error in Subroutine error:'
         write (errdev,*) '*** Message: Wrong Errorlevel'
         write (errdev,*) '*** Related Value: ', level
      endif

      if (level.eq.1) then 
         write (errdev,*) '*** Warning in Subroutine ',function_name,':'
      elseif (level.eq.2) then
         write (errdev,*) '*** Error in Subroutine ',function_name,':'
      else
         write (errdev,*) '*** Fatal Error in Subroutine ',
     $        function_name,':'
      endif
      write (errdev,*) '*** Message: ',message
      write (errdev,*) '*** Related Value: ',value 

      if (level.ge.3) then
         write (errdev,*)
         write (errdev,*) '*** Program stopped.'
         stop 137
      endif

      return
      end