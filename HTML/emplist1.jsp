<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%@page import="com.openlab.Employee"%>
<%@page import="org.apache.taglibs.standard.tag.common.core.ForEachSupport"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<title>emplist</title>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<link rel="stylesheet" type="text/css" href="css/style.css" />
	</head>
	<body>
		<div id="wrap">
			<div id="top_content"> 
				<div id="header">
					<div id="rightheader">
						<p>
							2009/11/20
							<br />
						</p>
					</div>
					<div id="topheader">
						<h1 id="title">
							<a href="#">main</a>
						</h1>
					</div>
					<div id="navigation">
					</div>
				</div>
				<div id="content">
					<p id="whereami">
					</p>
					<h1>
						Welcome!
					</h1>
					
					
				<%
				  ArrayList<Employee> es=(ArrayList<Employee>)request.getAttribute("es");
		
				
				
				
				 %>
					<table class="table">
						<tr class="table_header">
							<td>
								ID
							</td>
							<td>
								Name
							</td>
							<td>
								Salary
							</td>
							<td>
								Age
							</td>
							<td>
								Operation
							</td>
						</tr>
						<%
						   for(int i=0;i<es.size();i++){
						        Employee  e = es.get(i);
						      
						     
						
						
						 %>
						<tr class="row1"> 
							<td>
								<%=e.getEno()%>
							</td>
							<td>
								<%=e.getEname() %>
							</td>
							<td>
								<%=e.getJob() %>
							</td>
							<td>
								<%=e.getAge() %>
							</td>
							<td>
								<a href="emplist.html">delete emp</a>&nbsp;<a href="updateEmp.html">update emp</a>
							</td>
						</tr>
						<%
						
							}
						 %>
					</table>
					<p>
						<input type="button" class="button" value="Add Employee" onclick="location='addEmp.html'"/>
					</p>
				</div>
			</div>
			<div id="footer">
				<div id="footer_bg">
				ABC@126.com
				</div>
			</div>
		</div>
	</body>
</html>
