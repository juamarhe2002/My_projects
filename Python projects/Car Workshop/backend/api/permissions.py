from rest_framework import permissions

class IsAuthenticatedOrAdmin(permissions.IsAdminUser, permissions.IsAuthenticated):
    def has_permission(self, request, view):
        admin_permission = permissions.IsAdminUser.has_permission(request, view)
        auth_permission = permissions.IsAuthenticated.has_object_permission(request, view)
        return request.method == admin_permission or auth_permission