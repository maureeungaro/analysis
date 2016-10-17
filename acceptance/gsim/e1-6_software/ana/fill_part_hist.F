      SUBROUTINE FILL_PART_HIST
c
c_begin_doc
c  RCS ID string
c  $Id: fill_part_hist.F,v 1.12 2002/03/18 21:37:58 stepanya Exp $
c
c  Documentation for subroutine FILL_PART_HIST
c
c  Purpose:
c  --------
c
c  Input Parameters:  (Name - Type - Meaning)
c  ----------------
c
c  Output Parameters:  (Name - Type - Meaning)
c  -----------------
c
c  Other routines:
c  ---------------
c
c  Notes:
c  ------
c
c  Author:         Created:  Wed Jun 11 00:14:11 EDT 1997
c  -------
c
c  Major revisions:
c  ----------------
c     
c
c_end_doc
c
      IMPLICIT NONE
      SAVE
c
c_begin_inc
c  include files :
c  ---------------------
c BOS common block  uncomment the next line for BOS include file
#include "bcs.inc"
#include "wcs.inc"
#include "user_control.inc"
#include "seb_ntn.inc"
#include "clasmdl.inc"
c_end_inc
c
c_begin_var
c  input/output variables:
c  -----------------------
c
c  Local pre-defined variables:
c  ---------------------------
c  RCS information: 
      CHARACTER*132  CFILE, CREVIS, CSTATE, CDATE, CAUTHO, CRCSID
      PARAMETER (CFILE = '$RCSfile: fill_part_hist.F,v $')
      PARAMETER (CREVIS = '$Revision: 1.12 $')
      PARAMETER (CSTATE = '$State: Exp $')
      PARAMETER (CDATE = '$Date: 2002/03/18 21:37:58 $')
      PARAMETER (CAUTHO = '$Author: stepanya $')
      DATA CRCSID/   
     1'$Id: fill_part_hist.F,v 1.12 2002/03/18 21:37:58 stepanya Exp $'   
     2/   
c  Module information:
      CHARACTER*(*)  CRNAME, CRAUTH
      CHARACTER*100  CRMESS
      PARAMETER (CRNAME='FILL_PART_HIST')
      PARAMETER (CRAUTH='whoistheauthor')
c
c  Local User defined variables:
c  -----------------------------
      INTEGER NWRITE, mamind
      integer sect,hid,iecp,secth,ccphi
      integer ind,i,scstat,npip,npr,ng,npim
      real qx,qy,qz,p0x,p0y,p0z,m02,e0,thetah
      real ccsg,eec,stv
      real q2,w2,w,mp,pe,mpi,rfcor,r2d,phiel,phih,pi
      data mp,mpi,r2d,pi/0.938,0.139,57.29578,3.14159/
      real perp(6,3),perp_thickness,sc_ec_t,drc
      data perp_thickness/20.7/
      real thetael,thetapr,thetapip
c_end_var
c
c  executable code for routine FILL_PART_HIST:
c----6----------------------------------------------------------------72
c
      IF (NWRITE .LT. 1) THEN
        NWRITE = NWRITE + 1
        CRMESS='This is a DUMMY routine, this message written once'
        CALL RECMES(CRNAME,'I',CRMESS)
      ENDIF
      call hcdir('//PAWC',' ')
      call hcdir('//PAWC/SEB',' ')
      IECP=MAMIND(JW,'ECP ')
      ind=IECP+1
 10   ind=JW(ind-1)
      if(ind.gt.0)then
         sect=jw(ind-2)
         perp(sect,1)=rjw(ind+1)
         perp(sect,2)=rjw(ind+2)
         perp(sect,3)=rjw(ind+3)
         go to 10
      endif
      IF(npart.gt.0)THEN
         call hf1(3101,rf_time,1.)
         w=0.
         if(dc(1).gt.0.and.sc(1).gt.0.and.ec(1).gt.0.and.cc(1).gt.0)then
c
            if(stat(1).gt.0.and.dc_stat(dc(1)).gt.0.and.q(1).lt.0)then
            sect=int(dc_stat(dc(1))/100)
            eec=max(etot(ec(1)),ec_ei(ec(1))+ec_eo(ec(1)))
            call hf2(6300+sect,p(1),eec/p(1),1.)
            call hf2(6510+sect,eec/p(1),float(nphe(cc(1))),1.)
            hid=6000+sect
            if(nphe(cc(1)).gt.20)then
               call hf1(6300,eec/p(1),1.)
               q2=2.*ebeam*p(1)*(1.-cz(1))
               w2=mp**2+2.*mp*(ebeam-p(1))-q2
               qx=-p(1)*cx(1)
               qy=-p(1)*cy(1)
               qz=ebeam-p(1)*cz(1)
               thetael=acos(cz(1))*r2d
               phiel=atan2(cy(1),cx(1))*r2d
               if(phiel.lt.-30.)phiel=phiel+360.
               call hf1(6500,float(cc_sect(cc(1))),1.)
               ccphi=int(float(cc_segm(cc(1)))/1000.)
               ccsg=float(cc_segm(cc(1))-1000*ccphi)
               if(ccphi.eq.0)ccsg=-ccsg
               if(ccphi.ne.1)call hf1(6500+sect,ccsg/10.,1.)
               call hf2(6041,vz(1),phiel,1.)
               if(w2.gt.0)w=sqrt(w2)
               call hf1(6000,w,1.)
               call hf1(hid,w,1.)
               if(evntclas.gt.0)then
                  call hf1(6050,w,1.)
               elseif(evntclas.lt.0)then
                  call hf1(6060,w,1.)
               endif
               rfcor=sc_t(sc(1))-sc_r(sc(1))/29.98-tr_time
               call hf1(3102,rfcor,1.)
               call hf2(3120+sect,rfcor,float(sc_pd(sc(1))),1.)
               call hf2(3111,rf_time,rfcor,1.)
               call hf2(3112,rfcor,vz(dc(1)),1.)
c     Get ect-sct
               drc=perp(sect,1)
     *              *(dc_cxsc(dc(1))*cos(pi*(sect-1)/3.)-dc_cysc(dc(1))*sin(pi*(sect-1)/3.))
               drc=drc+perp(sect,2)
     *              *(dc_cysc(dc(1))*cos(pi*(sect-1)/3.)+dc_cxsc(dc(1))*sin(pi*(sect-1)/3.))      
               drc=drc+perp(sect,3)*dc_czsc(dc(1))
               sc_ec_t=ec_t(ec(1))-sc_t(sc(1))-perp_thickness/drc/29.979
               call hf1(6600,sc_ec_t,1.)
               call hf1(6600+sect,sc_ec_t,1.)
               call hf2(6640+sect,float(sc_pd(sc(1))),sc_ec_t,1.)
c     
               npr=0
               npip=0
               npim=0
               ng=0
               do i=2,npart
                  if(stat(i).gt.0.and.dc(i).gt.0.and.sc(i).gt.0)then
                     thetah=acos(cz(i))*r2d
                     phih =atan2(cy(1),cx(1))*r2d
                     if(phih .lt.-30.)phih =phih +360.
                     call hf2(6042,vz(i),phih ,1.)
                     scstat=sc_stat(sc(i))-(100*sc_pd(sc(i))+10000*sc_sect(sc(i)))
                     if(q(i).gt.0)then
                        hid=6100+sc_sect(sc(i))
                        call hf2(6310,p(i),edep(sc(i)),1.)
                        call hf2(6310+sc_sect(sc(i)),p(i),edep(sc(i)),1.)
                        if(m(i).gt.0.and.scstat.eq.33)call hf1(6100,sqrt(m(i)),1.)
                        call hf2(hid,float(sc_pd(sc(i))),m(i),1.)
                        call hf2(6200+sc_sect(sc(i)),p(i),thetah,1.)
                        call hf1(6220+sc_sect(sc(i)),float(sc_pd(sc(i))),1.)
                        if(ec(i).gt.0)then
                           secth=ec_sect(ec(i))
                           drc=perp(secth,1)
     *                          *(dc_cxsc(dc(i))*cos(pi*(secth-1)/3.)-dc_cysc(dc(i))*sin(pi*(secth-1)/3.))
                           drc=drc+perp(secth,2)
     *                          *(dc_cysc(dc(i))*cos(pi*(secth-1)/3.)+dc_cxsc(dc(i))*sin(pi*(secth-1)/3.))      
                           drc=drc+perp(secth,3)*dc_czsc(dc(i))
                           sc_ec_t=ec_t(ec(i))-sc_t(sc(i))-perp_thickness/drc/b(i)/29.979
                           call hf1(6610+secth,sc_ec_t,1.)
                        endif
                        if(id(i).eq.2212)then
                           npr=npr+1
                           stv=(sc_t(sc(i))-tr_time)-sc_r(sc(i))/29.979/(p(i)/sqrt(p(i)**2+mp**2))
                           call hf1(6110,stv,1.)
                           call hf2(hid+10,float(sc_pd(sc(i))),stv,1.)
                           p0x=qx-p(i)*cx(i)
                           p0y=qy-p(i)*cy(i)
                           p0z=qz-p(i)*cz(i)
                           e0=ebeam-p(1)-sqrt(p(i)**2+mp**2)+mp
                           m02=e0**2-p0x**2-p0y**2-p0z**2
                           call hf1(6401,m02,1.)
                           thetapr=acos(cz(i))*r2d
                        endif
                        if(id(i).eq.211)then
                           npip=npip+1
                           stv=(sc_t(sc(i))-tr_time)-sc_r(sc(i))/29.979/(p(i)/sqrt(p(i)**2+mpi**2))
                           call hf1(6120,stv,1.)
                           call hf2(hid+20,float(sc_pd(sc(i))),stv,1.)
                           p0x=qx-p(i)*cx(i)
                           p0y=qy-p(i)*cy(i)
                           p0z=qz-p(i)*cz(i)
                           e0=ebeam-p(1)-sqrt(p(i)**2+mpi**2)+mp
                           m02=e0**2-p0x**2-p0y**2-p0z**2
                           call hf1(6402,m02,1.)
                           thetapip=acos(cz(i))*r2d
                        endif
                     elseif(q(i).lt.0)then
                        npim=npim+1
                        call hf2(6210+sc_sect(sc(i)),p(i),thetah,1.)
                        call hf1(6230+sc_sect(sc(i)),float(sc_pd(sc(i))),1.)
                     endif
                  elseif(q(i).eq.0.and.ec(i).gt.0)then
                     ng=ng+1
                     call hf1(6620+ec_sect(ec(i)),b(i),1.)
                     eec=max(etot(ec(i)),ec_ei(ec(i))+ec_eo(ec(i)))
                     call hf2(6630+ec_sect(ec(i)),b(i),eec,1.)
                  endif
               enddo
            endif
         endif
      endif
      ENDIF
c
      if(npip.eq.1.and.npr.eq.0.and.npim.eq.0)then
c ep->epi+n
         if(m02.gt.0.8.and.m02.lt.1.05)call hf2(10101,thetael,thetapip,1.)
      elseif(npr.eq.1)then
c ep->epX
         call hf2(10102,thetael,m02,1.)
c ep->epgX
         if(ng.ge.1)call hf2(10112,thetael,m02,1.)
      endif
c
      RETURN
      END
c
c------------------------------------------------------------------------------




