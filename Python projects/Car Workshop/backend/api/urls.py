from django.urls import path
from . import views

urlpatterns = [
    path("employees/", views.EmployeeList.as_view(), name="employee-list"),
    path("employees/employee/", views.EmployeeSigned.as_view(), name="employee-signed"),
    path("employees/create/", views.EmployeeCreate.as_view(), name="employee-delete"),
    path("employees/delete/<int:pk>/", views.EmployeeDelete.as_view(), name="employee-delete"),
    path("tickets/", views.TicketList.as_view(), name="ticket-list"),
    path("tickets/create/", views.TicketCreate.as_view(), name="ticket-delete"),
    path("tickets/edit/<int:pk>/", views.TicketUpdate.as_view(), name="ticket-edit"),
    path("tickets/delete/<int:pk>/", views.TicketDelete.as_view(), name="ticket-delete"),
]