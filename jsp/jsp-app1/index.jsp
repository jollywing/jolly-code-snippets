<%@ page import="java.util.*" %>

<html>
  <head>
    <style>
      p {color:navy; background-color:lightgray; margin-bottom:5px; border-bottom:thin solid aqua;}
      body {margin:10px 3%;}
    </style>
    <title>Hello, Jsp world!</title>
  </head>
  <body>
    <h1>Hello, Jsp world!</h1>
    <%-- include directive --%>
    <p>Going to include hello.jsp...</p>
    <jsp:include page="average.jsp"/>

       <p>Now I use System.getProperty for various system properties such as java.version, java.home, os.name, user.name, user.home, user.dir etc. </p>
       <%-- use <%= %> to evaluate expression. --%>
       <table>
         <tr><td>java version</td><td><%= System.getProperty("java.version") %></td></tr>
         <tr><td>java home</td><td><%= System.getProperty("java.home") %></td></tr>
         <tr><td>OS name</td><td><%= System.getProperty("os.name") %></td></tr>
         <tr><td>User Name</td><td><%= System.getProperty("user.name") %></td></tr>
         <tr><td>User Home</td><td><%= System.getProperty("user.home") %></td></tr>
       </table>
       
       <p>The information of remote user is listed as follow:</p>
       <%-- predefined request variable --%>
       <table>
         <tr><td>Remote Host</td><td><%= request.getRemoteHost() %></td></tr>
         <tr><td>Remote User</td><td><%= request.getRemoteUser() %></td></tr>
         <tr><td>HTTP METHOD</td><td><%= request.getMethod() %></td></tr>
       </table>
       
       <p>Now, I will mix the scriptlets and HTML.</p>
       <%-- mix scriptlets and HTML --%>
       <table>
         <%
           String keyName;
           Properties p = System.getProperties();
           Enumeration enumKeys = p.propertyNames();
           while (enumKeys.hasMoreElements()) {
               keyName = (String)enumKeys.nextElement();
         %>
         <tr><td><%= keyName %></td><td><%= p.getProperty(keyName) %></td></tr>
         <%
              }
         %>
       </table>
       
       <%-- add method and variable declaration with <%! %> --%>
       <p>Now, I will add a declaration of getData() method.</p>
       <%!
               Date getDate() {
           System.out.println("getDate() method!");
           return new Date();
           }
       %>
       
       <p>getDate() returns <%= getDate() %></p>

  </body>
  
</html>

