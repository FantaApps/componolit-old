<?xml version="1.0" encoding="utf-8" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

   <xsl:output omit-xml-declaration="yes" method="xml" indent="yes" encoding="utf-8"/>

   <xsl:template match="@*|node()">
      <xsl:copy>
               <xsl:apply-templates select="@*|node()"/>
      </xsl:copy>
   </xsl:template>

   <xsl:template match="config/start">  
      <xsl:choose>
         <!-- Handle debug program -->
         <xsl:when test="@name=$gdb_prog">
            <start name="gdb_monitor">
               <config>
                  <target>
	                  <xsl:attribute name="name">
                        <xsl:value-of select="@name"/>
	                  </xsl:attribute>
                     <xsl:apply-templates select="binary"/>
                     <xsl:apply-templates select="config"/>
                  </target>
                  <preserve name="RAM" quantum="4M"/>
                  <vfs>
                     <dir name="dev">
                        <log/>
                     </dir>
                  </vfs>
                  <libc stdout="/dev/log" stderr="/dev/log"/>
               </config>

               <!--
                    If config has no route, make sure a terminal session to uart_drv is available
                    FIXME: This is not accurate, actuall we'd need to copy the defaul route here
                    and add the Terminal route.
               -->
               <xsl:if test="not(route)">
                  <route>
                     <service name="Terminal"> <child name="uart_drv"/> </service>
                     <any-service> <any-child/> <parent/> </any-service>
                  </route>
               </xsl:if>

               <xsl:apply-templates select="*[not(config)]"/>
            </start>
         </xsl:when>
         <xsl:otherwise>
            <xsl:copy>
               <xsl:apply-templates select="@*|node()"/>
            </xsl:copy>
         </xsl:otherwise>
      </xsl:choose>

      <!-- if config has no uart_drv, add one -->
      <xsl:if test="not(start[@name='uart_drv'])">
         <start name="uart_drv">
            <resource name="RAM" quantum="2M"/>
            <provides>
               <service name="Terminal"/>
               <service name="Uart"/>
            </provides>
            <config>
               <policy label_prefix="gdb_monitor" uart="1"/>
            </config>
            <route>
               <any-service> <parent/> </any-service>
            </route>
         </start>
      </xsl:if>
   </xsl:template>

   <!-- Config may not have IRQ or IO_PORT session, add if missing -->
   <xsl:template match="config/parent-provides">  
      <xsl:copy>
         <xsl:if test="not(service[@name='IRQ'])">
            <service name="IRQ"/>
         </xsl:if>
         <xsl:if test="not(service[@name='IO_PORT'])">
            <service name="IO_PORT"/>
         </xsl:if>
         <xsl:apply-templates select="@*|node()"/>
      </xsl:copy>
   </xsl:template>

</xsl:stylesheet>
